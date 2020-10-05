#include "simulationwidget.h"
#include "ui_simulationwidget.h"

#include "physicalgraphicobject.h"
#include "attributeeditorwidget.h"

#include <QPainter>
#include <QMouseEvent>

#include <QDragEnterEvent>
#include <QMimeData>

SimulationWidget::SimulationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationWidget)
{
    ui->setupUi(this);

    connect(ui->zoomWidget, &ZoomWidget::zoomUpdated,
            this, &SimulationWidget::updateZoom);

    connect(ui->zoomWidget, &ZoomWidget::fitRequested,
            this, &SimulationWidget::fitToContent);

    ui->timeControl->setUpdateTarget(this);
    ui->historyWidget->setTarget(this);

    setAcceptDrops(true);
}

SimulationWidget::~SimulationWidget()
{
    delete ui;
}

void SimulationWidget::addToSimulation(PhysicalObjectPtr physical, GraphicObjectPtr graphic)
{
    simulation.addSubject(physical);
    addGraphicObject(graphic);
}

void SimulationWidget::addGraphicObject(GraphicObjectPtr object)
{
    graphicObjects.append(object);
    saveCheckpoint();
    updateGeometry();
}

void SimulationWidget::removeGraphicObject(GraphicObjectPtr object)
{
    graphicObjects.removeOne(object);
    saveCheckpoint();
    updateGeometry();
}

void SimulationWidget::clearScene()
{
    graphicObjects.clear();
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

    for(auto& graphic : graphicObjects)
    {
        graphic->draw(&painter);
    }

    QWidget::paintEvent(event);
}

void SimulationWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint delta = event->pos() - clickedPoint;
    shouldSave = true;

    if(isTranslating)
        translation = oldTranslation + delta;
    else if (moveTarget)
        moveTarget->setPosition(toSimPosition(oldMoveTargetPos + delta));
    else
        shouldSave = false;

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
        moveTarget = getObjectAt(toSimPosition(clickedPoint));

        if(moveTarget)
            oldMoveTargetPos = fromSimPosition(moveTarget->pos());
    }
    else if(event->buttons() & Qt::RightButton)
    {
        GraphicObjectPtr graphic = getObjectAt(toSimPosition(clickedPoint));
        closeAttributeEdit();

        if(graphic)
            createAttributeEdit(graphic);
    }

    QWidget::mousePressEvent(event);
}

void SimulationWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(shouldSave)
        saveCheckpoint();

    shouldSave = false;
    isTranslating = false;
    moveTarget = nullptr;

    setCursor(Qt::ArrowCursor);
    QWidget::mouseReleaseEvent(event);
}

void SimulationWidget::wheelEvent(QWheelEvent *event)
{
    if(QApplication::keyboardModifiers() & Qt::CTRL)
    {
        int newZoom = scale * 100;
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

        SimulationGraphicObject* simGraphic = dynamic_cast<SimulationGraphicObject*>(clone.get());

        if(simGraphic)
            addToSimulation(simGraphic->getPhysical(), clone);
        else
            addGraphicObject(clone); 
    }

    QWidget::dropEvent(event);
}

GraphicObject *SimulationWidget::readDropData(QByteArray &itemData)
{
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    GraphicObject *graphic;

    dataStream.readRawData((char*)(&graphic), sizeof(graphic));
    return graphic;
}

GraphicObjectPtr SimulationWidget::getObjectAt(const QPoint &point)
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

void SimulationWidget::saveCheckpoint()
{
    saveToHistory();
    ui->timeControl->setCheckpoint(createState());
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

QPoint SimulationWidget::getContentCenter()
{
    QPoint center;

    for(const auto& graphic : graphicObjects)
        center += graphic->pos();
    center /= graphicObjects.size();

    return center;
}

void SimulationWidget::updateZoom(int zoom)
{
    scale = qMax(static_cast<qreal>(zoom) / 100.0, 0.1);
    updateView();
}

void SimulationWidget::fitToContent()
{
    QPoint newTranslation = rect().center() - getContentCenter();
    translation = newTranslation;
    updateView();
}
