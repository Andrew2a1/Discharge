#ifndef TIMECONTROLWIDGET_H
#define TIMECONTROLWIDGET_H

#include <QWidget>

class SimulationWidget;
class SimulationWidgetState;

namespace Ui {
class TimeControlWidget;
}

class TimeControlWidget : public QWidget
{
    Q_OBJECT


private:
    Ui::TimeControlWidget *ui;

    SimulationWidget *updateTarget = nullptr;
    SimulationWidgetState *checkpoint = nullptr;

    QTimer *timer;

    int simApplyTime = 100;
    bool isUpdating = false;

public:
    explicit TimeControlWidget(QWidget *parent = nullptr);
    ~TimeControlWidget();

    void setUpdateTarget(SimulationWidget *target);
    void setCheckpoint(SimulationWidgetState *newCheckpoint);
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
