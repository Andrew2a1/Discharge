#include "Simulation.h"
#include "PhysicalObject.h"
#include "SimulationState.h"

#include <vector>

void Simulation::clearSubjects()
{
    subjects.clear();
}

void Simulation::applyTime(double dt)
{
    if (subjects.size() == 1)
    {
        subjects.front()->applyTime(dt);
    }
    else if (subjects.size() > 1)
    {
        const Vector<double> vectZero = Vector<double>(subjects.front()->getPosition().size());
        std::vector<Vector<double>> forces(subjects.size(), vectZero);

        int i = 0;
        for (auto &subject : subjects)
        {
            for (auto &other : subjects)
            {
                if (subject != other)
                    forces[i] += subject->calculateForce(other.get());
            }
            ++i;
        }

        i = 0;
        for (auto &subject : subjects)
            subject->applyForce(forces[i++], dt);
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

    for (const auto &subject : subjects)
        simulationState->saveObject(subject);

    return simulationState;
}

void Simulation::restoreState(SimulationState *simulationState)
{
    std::list<PhysicalObjectPtr> savedObjects = simulationState->getSaved();

    auto iter = subjects.begin();
    while (iter != subjects.end())
    {
        if (simulationState->isSaved(*iter))
        {
            (*iter)->restore(simulationState->getData(*iter));
            ++iter;
        }
        else
        {
            iter = subjects.erase(iter);
        }
    }

    for (const auto &saved : savedObjects)
    {
        if (std::find(subjects.begin(), subjects.end(), saved) == subjects.end())
        {
            saved->restore(simulationState->getData(saved));
            addSubject(saved);
        }
    }
}
