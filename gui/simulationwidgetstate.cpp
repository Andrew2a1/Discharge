#include "simulationwidgetstate.h"
#include "physical/SimulationState.h"

SimulationWidgetState::SimulationWidgetState(QObject *parent) :
    QObject(parent)
{

}

SimulationWidgetState::~SimulationWidgetState()
{
    delete simState;
}
