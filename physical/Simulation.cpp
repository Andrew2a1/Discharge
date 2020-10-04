#include "Simulation.h"
#include "PhysicalObject.h"
#include "SimulationState.h"

void Simulation::clearSubjects()
{
    subjects.clear();
}

void Simulation::applyTime(double dt)
{
    if(subjects.size() == 1)
    {
        subjects.front()->applyTime(dt);
        return;
    }

    for(auto &subject : subjects)
        for(auto &other : subjects)
            applyForcesBetween(subject, other, dt);
}

void Simulation::applyForcesBetween(PhysicalObjectPtr obj, PhysicalObjectPtr other, double dt)
{
    if(obj != other)
    {
        const Vector<double> force = obj->calculateForce(other.get());
        obj->applyForce(force, dt);
    }
}

void Simulation::addSubject(PhysicalObjectPtr subject)
{
    subjects.push_back(subject);
}

void Simulation::removeSubject(PhysicalObjectPtr subject)
{
    subjects.remove(subject);
}

const std::list<PhysicalObjectPtr> &Simulation::getSubjects() const
{
    return subjects;
}

SimulationState *Simulation::saveState() const
{
    SimulationState *simulationState = new SimulationState();

    for(const auto& subject: subjects)
        simulationState->saveObject(subject);
    
    return simulationState;
}

void Simulation::restoreState(SimulationState * simulationState)
{
    std::list<PhysicalObjectPtr> savedObjects = simulationState->getSaved();

    for (const auto &subject : subjects)
    {
        if (simulationState->isSaved(subject))
            subject->restore(simulationState->getData(subject));
        else
            removeSubject(subject);
    }

    for(const auto &saved : savedObjects)
    {
        if(std::find(subjects.begin(), subjects.end(), saved) == subjects.end())
        {
            saved->restore(simulationState->getData(saved));
            addSubject(saved);
        }    
    }
}
