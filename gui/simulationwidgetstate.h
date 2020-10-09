#ifndef SIMULATIONWIDGETSTATE_H
#define SIMULATIONWIDGETSTATE_H

#include <QList>
#include "graphicobject.h"

class SimulationState;

class SimulationWidgetState
{
private:
    SimulationState *simState;
    QList<GraphicObjectPtr> graphicObjects;

public:
    ~SimulationWidgetState();

    SimulationState *state() const;
    void setState(SimulationState *value);

    QList<GraphicObjectPtr> getGraphicObjects() const;
    void setGraphicObjects(const QList<GraphicObjectPtr> &value);
};

typedef std::shared_ptr<SimulationWidgetState> SimulationWidgetStatePtr;

#endif // SIMULATIONWIDGETSTATE_H
