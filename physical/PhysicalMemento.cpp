#include "PhysicalMemento.h"
#include "PhysicalState.h"

void PhysicalMemento::setState(PhysicalState *state)
{
    this->state = state;
}

PhysicalState *PhysicalMemento::getState() const
{
    return state;
}

PhysicalMemento::~PhysicalMemento()
{
    delete state;
}
