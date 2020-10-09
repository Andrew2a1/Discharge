#ifndef TIMECONTROLWIDGET_H
#define TIMECONTROLWIDGET_H

#include <QWidget>
#include "simulationwidgetstate.h"

class SimulationWidget;

namespace Ui {
class TimeControlWidget;
}

class TimeControlWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::TimeControlWidget *ui;

    SimulationWidget *updateTarget = nullptr;
    SimulationWidgetStatePtr checkpoint = nullptr;

    QTimer *timer;

    int simApplyTime = 100;
    bool isUpdating = false;

public:
    explicit TimeControlWidget(QWidget *parent = nullptr);
    ~TimeControlWidget();

    void setUpdateTarget(SimulationWidget *target);
    void setCheckpoint(SimulationWidgetStatePtr newCheckpoint);
    int getSimApplyTime();

public slots:
    void setSimApplyTime(int newTime);

private:
    void timerTimeout();
    void updateButtons();

private slots:
    void startPressed();
    void stopPressed();
    void restoreCheckpoint();
};

#endif // TIMECONTROLWIDGET_H
