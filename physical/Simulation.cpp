#include "Simulation.h"
#include "PhysicalObject.h"
#include "SimulationState.h"

Simulation::~Simulation()
{
    for(auto &subject : subjects)
        delete subject;
}

void Simulation::applyTime(double dt)
{
    if(subjects.size() == 1)
    {
        subjects.front()->applyTime(dt);
        return;
    }

    for(auto &subject : subjects)
    {
        for(auto &other : subjects)
        {
            if(subject != other)
            {
                applyForcesBetween(subject, other, dt);
            }
        }
    }
}

void Simulation::applyForcesBetween(PhysicalObject *obj, PhysicalObject *other, double dt)
{
    const Vector<double> force = obj->calculateForce(other);
    obj->applyForce(force, dt);
}

void Simulation::addSubject(PhysicalObject *subject)
{
    subjects.push_back(subject);
}

void Simulation::removeSubject(PhysicalObject *subject)
{
    subjects.remove(subject);
}

void Simulation::clearSubjects()
{
    subjects.clear();
}

const std::list<PhysicalObject *> &Simulation::getSubjects() const
{
    return subjects;
}

SimulationState *Simulation::saveState() const
{
    SimulationState *simulationState = new SimulationState(subjects);
    return simulationState;
}

void Simulation::restoreState(SimulationState *simulationState)
{
    simulationState->restoreState();
}
