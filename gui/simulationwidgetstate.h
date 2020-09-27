#ifndef SIMULATIONWIDGETSTATE_H
#define SIMULATIONWIDGETSTATE_H

#include <QObject>
#include "simulationwidget.h"

class SimulationState;

class SimulationWidgetState : public QObject
{
    Q_OBJECT

public:
    SimulationState *simState;
    QList<GraphicObject*> graphicObjects;

public:
    explicit SimulationWidgetState(QObject *parent = nullptr);
    ~SimulationWidgetState();

};

#endif // SIMULATIONWIDGETSTATE_H
