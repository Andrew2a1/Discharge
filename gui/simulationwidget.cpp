#include "simulationwidget.h"
#include "ui_simulationwidget.h"

#include "simulationwidgetstate.h"
#include "simulationgraphicobject.h"

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

void SimulationWidget::addToSimulation(SimulationGraphicObject *object)
{
    addGraphicObject(object);
    simulation.addSubject(object->getPhysical());
}

void SimulationWidget::addGraphicObject(GraphicObject *object)
{
    graphicObjects.append(object);
    saveCheckpoint();
    updateGeometry();
}

void SimulationWidget::removeGraphicObject(GraphicObject *object)
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
    updateGeometry();
}

SimulationWidgetState *SimulationWidget::createState()
{
    SimulationWidgetState *widgetState = new SimulationWidgetState(this);
    widgetState->simState = simulation.saveState();
    widgetState->graphicObjects = graphicObjects;
    return widgetState;
}

void SimulationWidget::restoreState(SimulationWidgetState *state)
{
    simulation.restoreState(state->simState);
    graphicObjects = state->graphicObjects;
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
    if(isTranslating)
    {
        translation = oldTranslation + (event->pos() - clickedPoint);
        updateGeometry();
    }

    QWidget::mouseMoveEvent(event);
}

void SimulationWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::MiddleButton)
    {
        setCursor(Qt::SizeAllCursor);

        isTranslating = true;
        clickedPoint = event->pos();
        oldTranslation = translation;
    }

    QWidget::mousePressEvent(event);
}

void SimulationWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isTranslating = false;
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
        GraphicObject *cpy = readDropData(itemData)->clone();
        cpy->setPosition(event->pos());

        SimulationGraphicObject* simGraphic = dynamic_cast<SimulationGraphicObject*>(cpy);

        if(simGraphic)
            addToSimulation(simGraphic);
        else
            addGraphicObject(cpy);
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

void SimulationWidget::saveCheckpoint()
{
    saveToHistory();
    ui->timeControl->setCheckpoint(createState());
}

void SimulationWidget::saveToHistory()
{
    ui->historyWidget->save(createState());
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
    updateGeometry();
}

void SimulationWidget::fitToContent()
{
    QPoint newTranslation = rect().center() - getContentCenter();
    translation = newTranslation;
    updateGeometry();
}
