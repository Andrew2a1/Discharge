#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>

namespace Ui {
class SimulationWidget;
}

class SimulationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationWidget(QWidget *parent = nullptr);
    ~SimulationWidget();

private:
    Ui::SimulationWidget *ui;
};

#endif // SIMULATIONWIDGET_H
