#include "simulationwidget.h"
#include "ui_simulationwidget.h"

#include "simulationgraphicobject.h"
#include "physicalgraphicobject.h"
#include "electrostaticgraphicobject.h"
#include "attributeeditorwidget.h"

#include "physical/PhysicalObject.h"
#include "physical/ElectricCharge.h"
#include "physical/PhysicalObjectPtr.h"

#include <QPainter>
#include <QMouseEvent>

#include <QDragEnterEvent>
#include <QMimeData>

SimulationWidget::SimulationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationWidget)
{
    ui->setupUi(this);
    selection = new SelectionManager(graphicObjects, this);

    connect(ui->zoomWidget, &ZoomWidget::zoomUpdated,
            this, &SimulationWidget::updateZoom);

    connect(ui->zoomWidget, &ZoomWidget::fitRequested,
            this, &SimulationWidget::fitToContent);

    ui->timeControl->setUpdateTarget(this);
    ui->historyWidget->setTarget(this);

    setFocusPolicy(Qt::ClickFocus);
    setAcceptDrops(true);

    saveCheckpoint();
}

SimulationWidget::~SimulationWidget()
{
    delete ui;
}

void SimulationWidget::setCopyManager(CopyManager *manager)
{
    copyManager = manager;
}

void SimulationWidget::setPrototypeManager(PrototypeManager *manager)
{
    prototypeManager = manager;
}

void SimulationWidget::addGraphicObject(GraphicObjectPtr object, bool addToSim)
{
    SimulationGraphicObject* simulated = dynamic_cast<SimulationGraphicObject*>(object.get());

    if(addToSim && simulated)
        simulation.addSubject(simulated->getPhysical());

    graphicObjects.append(object);
    saveCheckpoint();
    updateGeometry();
}

void SimulationWidget::removeGraphicObject(GraphicObjectPtr object)
{
    SimulationGraphicObject* simulated = dynamic_cast<SimulationGraphicObject*>(object.get());

    if(simulated)
        simulation.removeSubject(simulated->getPhysical());

    if(attrEditor && attrEditor->getTarget() == object.get())
        closeAttributeEdit();

    graphicObjects.removeOne(object);

    saveCheckpoint();
    updateGeometry();
}

void SimulationWidget::clearScene()
{
    closeAttributeEdit();
    selection->clear();

    graphicObjects.clear();
    simulation.clearSubjects();

    saveCheckpoint();
    updateGeometry();
}

void SimulationWidget::applyTime(double dt)
{
    simulation.applyTime(dt);
    updateView();
}

SimulationWidgetStatePtr SimulationWidget::createState()
{
    SimulationWidgetStatePtr widgetState(new SimulationWidgetState);
    widgetState->setState(simulation.saveState());
    widgetState->setGraphicObjects(graphicObjects);
    return widgetState;
}

void SimulationWidget::restoreState(SimulationWidgetStatePtr state)
{
    simulation.restoreState(state->state());
    graphicObjects = state->getGraphicObjects();
}

void SimulationWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(translation);
    painter.scale(scale, scale);

    if(isSelecting)
        painter.drawRect(selection->getRect());

    for(auto& graphic : graphicObjects)
    {
        graphic->draw(&painter);

        if(selection->contains(graphic))
            painter.drawRect(graphic->getBounds());
    }


    QWidget::paintEvent(event);
}

void SimulationWidget::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Delete)) {
        handleDelete();
    }
    else if(event->matches(QKeySequence::Copy)) {
        handleCopy();
    }
    else if(event->matches(QKeySequence::Cut)) {
        handleCut();
    }
    else if(event->matches(QKeySequence::Paste)) {
        handlePaste();
    }
    else if(event->matches(QKeySequence::Undo)) {
        undo();
    }
    else if(event->matches(QKeySequence::Redo)) {
        redo();
    }

    QWidget::keyPressEvent(event);
}

void SimulationWidget::handleDelete()
{
    if(!selection->isEmpty())
    {
        for(auto &obj : selection->getSelected())
            removeGraphicObject(obj);

        selection->clear();
    }
}

void SimulationWidget::handleCopy()
{
    if(copyManager && !selection->isEmpty())
    {
        QList<GraphicObjectPtr> copied;

        for(const auto& obj : selection->getSelected())
            copied.append(GraphicObjectPtr(obj->clone()));

        copyManager->setCopied(copied);
    }
}

void SimulationWidget::handleCut()
{
    if(copyManager && !selection->isEmpty())
    {
        QList<GraphicObjectPtr> copied;

        for(const auto& obj : selection->getSelected()) {
            copied.append(GraphicObjectPtr(obj->clone()));
            removeGraphicObject(obj);
        }

        copyManager->setCopied(copied);
        selection->clear();
    }
}

void SimulationWidget::handlePaste()
{
    pasteTranslated();
}

void SimulationWidget::undo()
{
    ui->historyWidget->undo();
}

void SimulationWidget::redo()
{
    ui->historyWidget->redo();
}

void SimulationWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint delta = event->pos() - clickedPoint;

    if(isTranslating) {
        translation = oldTranslation + delta;
    }
    else if(isSelecting) {
        clearSelectionIfNotMultiply();
        selection->addFromRect(QRect(toSimPosition(clickedPoint), toSimPosition(event->pos())));
    }
    else if (!selection->isEmpty() && isMoving) {
        for(auto &obj : selection->getSelected())
            obj->setPosition(obj->pos() + (event->pos() - oldMovePos)/scale);
        shouldSave = true;
    }

    oldMovePos = event->pos();
    updateView();

    QWidget::mouseMoveEvent(event);
}

void SimulationWidget::mousePressEvent(QMouseEvent *event)
{
    clickedPoint = event->pos();

    if(event->buttons() & Qt::MiddleButton)
    {
        setCursor(Qt::SizeAllCursor);

        isTranslating = true;
        oldTranslation = translation;
    }
    else if(event->buttons() & Qt::LeftButton)
    {
        closeAttributeEdit();

        GraphicObjectPtr lastClicked = getObjectAt(toSimPosition(clickedPoint));
        oldMovePos = clickedPoint;
        isMoving = true;

        if(!lastClicked) {
            clearSelectionIfNotMultiply();
            isSelecting = true;
            isMoving = false;
        }
        else if(!selection->contains(toSimPosition(clickedPoint))) {
            clearSelectionIfNotMultiply();
            selection->add(lastClicked);
        }
    }
    else if(event->buttons() & Qt::RightButton)
    {
        closeAttributeEdit();
        if(!selection->contains(toSimPosition(clickedPoint)))
            selection->clear();
    }

    updateView();
    QWidget::mousePressEvent(event);
}

void SimulationWidget::clearSelectionIfNotMultiply()
{
    if(!selectMultiply())
        selection->clear();
}

bool SimulationWidget::selectMultiply() const
{
    return (QApplication::keyboardModifiers() & Qt::SHIFT) ||
            (QApplication::keyboardModifiers() & Qt::CTRL);
}

void SimulationWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(shouldSave)
        saveCheckpoint();

    isSelecting = false;
    shouldSave = false;
    isTranslating = false;
    isMoving = false;

    setCursor(Qt::ArrowCursor);
    updateView();

    QWidget::mouseReleaseEvent(event);
}

void SimulationWidget::contextMenuEvent(QContextMenuEvent *event)
{
    GraphicObjectPtr graphic = getObjectAt(toSimPosition(clickedPoint));
    QMenu *contextMenu = new QMenu(this);

    if(graphic)
    {
        contextMenu->addAction("Edit", [=](){createAttributeEdit(graphic);});
        contextMenu->addSeparator();

        contextMenu->addAction("Cut", [=](){
            selection->add(graphic);
            handleCut();
        });

        contextMenu->addAction("Copy", [=](){
            selection->add(graphic);
            handleCopy();
            selection->clear();
        });

        contextMenu->addSeparator();
        contextMenu->addAction("Delete", [=](){
            selection->add(graphic);
            handleDelete();
        });
    }
    else
    {
        QMenu *addMenu = contextMenu->addMenu("Add");
        fillAddMenu(addMenu);

        if(hasPasteData()) {
            contextMenu->addSeparator();
            contextMenu->addAction("Paste", this, &SimulationWidget::handlePaste);
            contextMenu->addAction("Paste here", [=](){
                pasteTranslated(toSimPosition(clickedPoint)
                                -getCenter(copyManager->getCopied()));
            });
        }
    }

    contextMenu->popup(event->globalPos());
    QWidget::contextMenuEvent(event);
}

void SimulationWidget::wheelEvent(QWheelEvent *event)
{
    if(QApplication::keyboardModifiers() & Qt::CTRL)
    {
        int newZoom = static_cast<int>(scale * 100);
        newZoom += event->angleDelta().y() / 16;
        ui->zoomWidget->setZoom(newZoom);
    }

    QWidget::wheelEvent(event);
}

void SimulationWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata") &&
            event->source())
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void SimulationWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        GraphicObjectPtr clone(readDropData(itemData)->clone());

        clone->setPosition(toSimPosition(event->pos()));
        addGraphicObject(clone);
    }

    QWidget::dropEvent(event);
}

GraphicObject *SimulationWidget::readDropData(QByteArray &itemData) const
{
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    GraphicObject *graphic;

    dataStream.readRawData(reinterpret_cast<char*>(&graphic), sizeof(graphic));
    return graphic;
}

GraphicObjectPtr SimulationWidget::getObjectAt(const QPoint &point) const
{
    for(const auto& object : graphicObjects)
        if(object->covers(point))
            return object;

    return nullptr;
}

QPoint SimulationWidget::toSimPosition(const QPoint &windowPos) const
{
    return (windowPos - translation)/scale;
}

QPoint SimulationWidget::fromSimPosition(const QPoint &simPos) const
{
    return simPos * scale + translation;
}

void SimulationWidget::fillAddMenu(QMenu *addMenu)
{
    for(const auto &name : prototypeManager->names())
    {
        addMenu->addAction(name, [=](){
            GraphicObjectPtr obj(prototypeManager->get(name)->clone());
            addGraphicObject(obj);
            obj->setPosition(toSimPosition(clickedPoint));
        });
    }
}

void SimulationWidget::pasteTranslated(const QPoint &translation)
{
    if(copyManager && !copyManager->isEmpty())
    {
        selection->clear();

        for(auto &obj : copyManager->getCopied())
        {
            GraphicObjectPtr added(obj->clone());
            added->setPosition(obj->pos() + translation);

            addGraphicObject(added);
            selection->add(added);
        }
    }
}

void SimulationWidget::saveCheckpoint()
{
    saveToHistory();
    ui->timeControl->setCheckpoint(createState());
}

bool SimulationWidget::hasSelected() const
{
    return !selection->isEmpty();
}

bool SimulationWidget::hasPasteData() const
{
    return !copyManager->isEmpty();
}

bool SimulationWidget::hasHistoryNext() const
{
    return ui->historyWidget->hasNext();
}

bool SimulationWidget::hasHistoryPrevious() const
{
    return ui->historyWidget->hasPrevious();
}

unsigned char SimulationWidget::typeID() const
{
    return 127;
}

SavableData *SimulationWidget::save() const
{
    return simulation.save();
}

bool SimulationWidget::restore(SavableData *data)
{
    clearScene();

    if(!simulation.restore(data))
        return false;

    for(const auto& subject: simulation.getSubjects())
    {
        ElectricChargePtr electric(std::dynamic_pointer_cast<ElectricCharge>(subject));

        if(electric)
            addGraphicObject(GraphicObjectPtr(new ElectrostaticGraphicObject(electric)), false);
        else
            addGraphicObject(GraphicObjectPtr(new PhysicalGraphicObject(subject)), false);
    }

    return true;
}

void SimulationWidget::saveToHistory()
{
    ui->historyWidget->save(createState());
}

void SimulationWidget::createAttributeEdit(GraphicObjectPtr obj)
{
    attrEditor = obj->createAttributeEditor(this);

    const QSize &size = attrEditor->sizeHint();
    const QPoint &newPos = fromSimPosition(obj->pos());

    attrEditor->setGeometry(newPos.x(), newPos.y(),
                            size.width() + 40, size.height() + 20);
    attrEditor->show();
}

void SimulationWidget::closeAttributeEdit()
{
    if(attrEditor)
    {
        attrEditor->close();
        attrEditor = nullptr;
    }
}

void SimulationWidget::updateView()
{
    if(attrEditor)
    {
        const QPoint newPos = fromSimPosition(attrEditor->getTarget()->pos());

        attrEditor->setGeometry(newPos.x(),
                                newPos.y(),
                                attrEditor->width(),
                                attrEditor->height());
    }

    updateGeometry();
}

QPoint SimulationWidget::getCenter(const QList<GraphicObjectPtr> &objects) const
{
    QPoint center;

    for(const auto& graphic : objects)
        center += graphic->pos();
    center /= objects.size();

    return center;
}

void SimulationWidget::updateZoom(int zoom)
{
    scale = qMax(static_cast<qreal>(zoom) / 100.0, 0.1);
    updateView();
}

void SimulationWidget::fitToContent()
{
    QPoint newTranslation = rect().center() - getCenter(graphicObjects);
    translation = newTranslation;
    updateView();
}
