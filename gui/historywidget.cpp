#include "historywidget.h"
#include "ui_historywidget.h"
#include "simulationwidget.h"

HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);

    connect(ui->redoButton, &QPushButton::clicked, this, &HistoryWidget::redo);
    connect(ui->undoButton, &QPushButton::clicked, this, &HistoryWidget::undo);

    connect(this, &HistoryWidget::undoEnabled, ui->undoButton, &QPushButton::setEnabled);
    connect(this, &HistoryWidget::redoEnabled, ui->redoButton, &QPushButton::setEnabled);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

void HistoryWidget::setTarget(SimulationWidget *simWidget)
{
    simulationWidget = simWidget;
}

void HistoryWidget::save(SimulationWidgetStatePtr state)
{
    history.add(state);
    updateStatus();
}

void HistoryWidget::setMaxHistoryLen(unsigned max)
{
    history.setMaxSize(max);
}

bool HistoryWidget::hasNext() const
{
    return history.hasNext();
}

bool HistoryWidget::hasPrevious() const
{
    return history.hasPrevious();
}

void HistoryWidget::updateStatus()
{
    emit redoEnabled(hasNext());
    emit undoEnabled(hasPrevious());
}

void HistoryWidget::undo()
{
    if(simulationWidget && history.hasPrevious())
        simulationWidget->restoreState(history.previous());

    updateStatus();
    simulationWidget->updateGeometry();
}

void HistoryWidget::redo()
{
    if(simulationWidget && history.hasNext())
        simulationWidget->restoreState(history.next());

    updateStatus();
    simulationWidget->updateGeometry();
}
