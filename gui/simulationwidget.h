#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QList>

#include "physical/Simulation.h"
#include "physical/PhysicalObjectPtr.h"

#include "graphicobject.h"
#include "selectionmanager.h"
#include "simulationwidgetstate.h"

#include "copymanager.h"

namespace Ui {
class SimulationWidget;
}

class SimulationWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::SimulationWidget *ui;

    AttributeEditorWidget *attrEditor = nullptr;
    CopyManager *copyManager = nullptr;
    SelectionManager *selection;

    Simulation simulation;
    QList<GraphicObjectPtr> graphicObjects;

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

    void setCopyManager(CopyManager *manager);

    void addGraphicObject(GraphicObjectPtr object);
    void removeGraphicObject(GraphicObjectPtr object);
    void clearScene();

    void applyTime(double dt);

    SimulationWidgetStatePtr createState();
    void restoreState(SimulationWidgetStatePtr state);

    void saveCheckpoint();

public slots:
    void handleCopy();
    void handleCut();
    void handlePaste();

    void undo();
    void redo();

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
    GraphicObject *readDropData(QByteArray &itemData) const;
    GraphicObjectPtr getObjectAt(const QPoint& point) const;

    QPoint toSimPosition(const QPoint &windowPos) const;
    QPoint fromSimPosition(const QPoint &simPos) const;

    bool selectMultiply() const;
    void clearSelectionIfNotMultiply();

    QPoint getContentCenter() const;
    void saveToHistory();

    void createAttributeEdit(GraphicObjectPtr obj);
    void closeAttributeEdit();

    void updateView();

private slots:
    void updateZoom(int zoom);
    void fitToContent();
};

#endif // SIMULATIONWIDGET_H
