#include "timecontrolwidget.h"
#include "ui_timecontrolwidget.h"
#include "simulationwidget.h"

#include <QTimer>
#include <QPushButton>

TimeControlWidget::TimeControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeControlWidget)
{
    ui->setupUi(this);

    updateButtons();

    timer = new QTimer(this);
    timer->setInterval(1000 / 60);

    connect(timer, &QTimer::timeout, this, &TimeControlWidget::timerTimeout);
    connect(ui->startButton, &QPushButton::clicked, this, &TimeControlWidget::startPressed);
    connect(ui->pauseButton, &QPushButton::clicked, this, &TimeControlWidget::stopPressed);
    connect(ui->timeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateTimeChanged(int)));
}

TimeControlWidget::~TimeControlWidget()
{
    delete ui;
}

void TimeControlWidget::setUpdateTarget(SimulationWidget *target)
{
    updateTarget = target;
}

void TimeControlWidget::timerTimeout()
{
    if(updateTarget)
        updateTarget->applyTime(static_cast<double>(simApplyTime) / 1000.0);
}

void TimeControlWidget::updateButtons()
{
    ui->startButton->setChecked(isUpdating);
    ui->pauseButton->setChecked(!isUpdating);
}

void TimeControlWidget::updateTimeChanged(int newTime)
{
    simApplyTime = newTime;
}

void TimeControlWidget::startPressed()
{
    isUpdating = true;
    timer->start();
    updateButtons();
}

void TimeControlWidget::stopPressed()
{
    isUpdating = false;
    timer->stop();
    updateButtons();
}
