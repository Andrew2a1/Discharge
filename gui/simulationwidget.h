#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QList>

#include "physical/Simulation.h"
#include "graphicobject.h"

class SimulationWidgetState;
class SimulationGraphicObject;

namespace Ui {
class SimulationWidget;
}

class SimulationWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::SimulationWidget *ui;
    Simulation simulation;

    QList<GraphicObject*> graphicObjects;

    QPoint translation;
    QPoint clickedPoint;
    QPoint oldTranslation;

    qreal scale = 1.0;
    bool isTranslating = false;

public:
    explicit SimulationWidget(QWidget *parent = nullptr);
    ~SimulationWidget();

    void addToSimulation(SimulationGraphicObject *object);
    void addGraphicObject(GraphicObject *object);

    void removeGraphicObject(GraphicObject *object);
    void clearScene();

    void applyTime(double dt);

    SimulationWidgetState *createState();
    void restoreState(SimulationWidgetState *state);

    void saveCheckpoint();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    GraphicObject *readDropData(QByteArray &itemData);

    void saveToHistory();
    QPoint getContentCenter();

private slots:
    void updateZoom(int zoom);
    void fitToContent();
};

#endif // SIMULATIONWIDGET_H
