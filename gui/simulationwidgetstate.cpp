#include "simulationwidgetstate.h"
#include "physical/SimulationState.h"

SimulationWidgetState::~SimulationWidgetState()
{
    delete simState;
}

QList<GraphicObjectPtr> SimulationWidgetState::getGraphicObjects() const
{
    return graphicObjects;
}

void SimulationWidgetState::setGraphicObjects(const QList<GraphicObjectPtr> &value)
{
    graphicObjects = value;
}

SimulationState *SimulationWidgetState::state() const
{
    return simState;
}

void SimulationWidgetState::setState(SimulationState *value)
{
    simState = value;
}
