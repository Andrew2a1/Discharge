#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include "toolbox/history.h"

class SimulationWidget;
class SimulationWidgetState;
typedef History<SimulationWidgetState*> SimulationHistory;

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
    void save(SimulationWidgetState *state);
    void setMaxHistoryLen(unsigned max);

private:
    void updateButtons();

private slots:
    void restorePrevious();
    void restoreNext();
};

#endif // HISTORYWIDGET_H
