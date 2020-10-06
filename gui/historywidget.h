#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include "simulationwidgetstate.h"
#include "toolbox/history.h"

class SimulationWidget;

typedef History<SimulationWidgetStatePtr> SimulationHistory;

namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::HistoryWidget *ui;
    SimulationWidget *simulationWidget = nullptr;
    SimulationHistory history;

public:
    explicit HistoryWidget(QWidget *parent = nullptr);
    ~HistoryWidget();

    void setTarget(SimulationWidget *simWidget);
    void save(SimulationWidgetStatePtr state);
    void setMaxHistoryLen(unsigned max);

public slots:
    void undo();
    void redo();

private:
    void updateButtons();

};

#endif // HISTORYWIDGET_H
