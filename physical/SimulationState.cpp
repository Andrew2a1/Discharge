#include "SimulationState.h"
#include "PhysicalObject.h"
#include "Simulation.h"

#include <algorithm>

SimulationState::SimulationState(const std::list<PhysicalObject*> &subjects)
{
    for(const auto &subject : subjects)
        addMementoFrom(subject);
}

SimulationState::~SimulationState()
{
    clear();
}

void SimulationState::addMementoFrom(PhysicalObject *object)
{
    
}

void SimulationState::removeMemento(PhysicalObject *object)
{
    for(auto &memento : mementos)
    {
        if(memento->object == object)
        {
            mementos.remove(memento);

            delete memento->memento;
            delete memento;
        } 
    }  
}

void SimulationState::clear()
{
    for(auto &memento : mementos)
    {
        delete memento->memento;
        delete memento;
    }  

    mementos.clear();
}

void SimulationState::restoreState(Simulation *simulation)
{
    
}

bool SimulationState::containsPhysical(const std::list<PhysicalObject *> &objects, const PhysicalObject *physical) const
{
    return std::find(objects.begin(), objects.end(), physical) != objects.end();
}

bool SimulationState::isObjectInMementos(const PhysicalObject *physical) const
{
    for(auto &memento : mementos)
        if(memento->object == physical)
            return true;

    return false;
}
