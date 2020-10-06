#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QList>

#include "physical/Simulation.h"
#include "physical/PhysicalObjectPtr.h"

#include "graphicobject.h"
#include "simulationwidgetstate.h"

namespace Ui {
class SimulationWidget;
}

class SimulationWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::SimulationWidget *ui;

    Simulation simulation;
    QList<GraphicObjectPtr> graphicObjects;
    AttributeEditorWidget *attrEditor = nullptr;

    QList<GraphicObjectPtr> selected;
    QRect selection;
    QPoint oldMovePos;

    QPoint translation;
    QPoint clickedPoint;
    QPoint oldTranslation;

    qreal scale = 1.0;

    bool isTranslating = false;
    bool isSelecting = false;
    bool isMoving = false;
    bool shouldSave = false;

public:
    explicit SimulationWidget(QWidget *parent = nullptr);
    ~SimulationWidget();

    void addToSimulation(PhysicalObjectPtr physical, GraphicObjectPtr graphic);

    void addGraphicObject(GraphicObjectPtr object);
    void removeGraphicObject(GraphicObjectPtr object);
    void clearScene();

    void applyTime(double dt);

    SimulationWidgetStatePtr createState();
    void restoreState(SimulationWidgetStatePtr state);

    void saveCheckpoint();

protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    GraphicObject *readDropData(QByteArray &itemData);
    GraphicObjectPtr getObjectAt(const QPoint& point);

    QPoint toSimPosition(const QPoint &windowPos) const;
    QPoint fromSimPosition(const QPoint &simPos) const;

    QPoint getContentCenter();
    void saveToHistory();

    void createAttributeEdit(GraphicObjectPtr obj);
    void closeAttributeEdit();

    void updateView();

private slots:
    void updateZoom(int zoom);
    void fitToContent();
};

#endif // SIMULATIONWIDGET_H
