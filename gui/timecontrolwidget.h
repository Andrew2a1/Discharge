#ifndef TIMECONTROLWIDGET_H
#define TIMECONTROLWIDGET_H

#include <QWidget>

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
    QTimer *timer;

    int simApplyTime = 100;
    bool isUpdating = false;

public:
    explicit TimeControlWidget(QWidget *parent = nullptr);
    ~TimeControlWidget();

    void setUpdateTarget(SimulationWidget *target);

private:
    void timerTimeout();
    void updateButtons();

private slots:
    void updateTimeChanged(int newTime);

    void startPressed();
    void stopPressed();
};

#endif // TIMECONTROLWIDGET_H
