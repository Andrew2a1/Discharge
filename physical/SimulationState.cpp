#include "SimulationState.h"
#include "PhysicalMemento.h"
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

void SimulationState::restoreState(Simulation *simulation)
{
    const std::list<PhysicalObject *> &subjects = simulation->getSubjects();

    for(auto &subject : subjects)
        if(!isObjectInMementos(subject))
            simulation->removeSubject(subject);

    for(auto &memento : mementos)
    {
        if(!containsPhysical(subjects, memento->object))
        {
            memento->object = new PhysicalObject;
            simulation->addSubject(memento->object);
        }

        memento->object->restoreMemento(memento->memento);
    }
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
