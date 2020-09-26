#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>
#include <QPoint>

namespace Ui {
class SimulationWidget;
}

class SimulationWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::SimulationWidget *ui;

    QPoint translation;
    QPoint clickedPoint;
    QPoint oldTranslation;

    qreal scale = 1.0;
    bool isTranslating = false;

public:
    explicit SimulationWidget(QWidget *parent = nullptr);
    ~SimulationWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private slots:
    void updateZoom(int zoom);
    void fitToContent();
};

#endif // SIMULATIONWIDGET_H
