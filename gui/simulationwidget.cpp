#include "simulationwidget.h"
#include "ui_simulationwidget.h"

#include <QPainter>
#include <QMouseEvent>

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
}

SimulationWidget::~SimulationWidget()
{
    delete ui;
}

void SimulationWidget::addToSimulation(PhysicalObject *physical)
{
    simulation.addSubject(physical);
}

void SimulationWidget::addGraphicObject(GraphicObject *object)
{
    graphicObjects.append(object);
}

void SimulationWidget::removeGraphicObject(GraphicObject *object)
{
    graphicObjects.removeOne(object);
}

void SimulationWidget::clearScene()
{
    graphicObjects.clear();
}

void SimulationWidget::applyTime(double dt)
{
    simulation.applyTime(dt);
    updateGeometry();
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

void SimulationWidget::updateZoom(int zoom)
{
    scale = qMax(static_cast<qreal>(zoom) / 100.0, 0.05);
    updateGeometry();
}

void SimulationWidget::fitToContent()
{
    int newZoom = scale * 100;

    // TODO

    ui->zoomWidget->setZoom(newZoom);
}