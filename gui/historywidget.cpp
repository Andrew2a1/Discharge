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
    updateButtons();
}

void HistoryWidget::setMaxHistoryLen(unsigned max)
{
    history.setMaxSize(max);
}

void HistoryWidget::updateButtons()
{
    ui->redoButton->setEnabled(history.hasNext());
    ui->undoButton->setEnabled(history.hasPrevious());
}

void HistoryWidget::undo()
{
    if(simulationWidget && history.hasPrevious())
        simulationWidget->restoreState(history.previous());

    updateButtons();
    simulationWidget->updateGeometry();
}

void HistoryWidget::redo()
{
    if(simulationWidget && history.hasNext())
        simulationWidget->restoreState(history.next());

    updateButtons();
    simulationWidget->updateGeometry();
}
