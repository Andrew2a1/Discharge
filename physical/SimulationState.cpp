#include "SimulationState.h"
#include "PhysicalMemento.h"
#include "PhysicalObject.h"

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
    ObjectMemento* memento = new ObjectMemento{object, object->createMemento()};
    mementos.push_back(memento);
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

void SimulationState::restoreState()
{
    for(auto &memento : mementos)
    {
        memento->object->restoreMemento(memento->memento);
    }

    clear();
}