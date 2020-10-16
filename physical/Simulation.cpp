#include "Simulation.h"
#include "SimulationState.h"

#include "physical/SimulationSubject.h"
#include "SimulationSubjectPtr.h"

#include "toolbox/SavableData.h"
#include <vector>

void Simulation::clearSubjects()
{
    subjects.clear();
}

void Simulation::applyTime(RealNumber dt)
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
                {
                    forces[i] += subject->calculateForce(other.get());

                    if(subject->isCollision(other.get())) {
                        subject->collide(other.get());
                    }
                }
            }
            ++i;
        }

        i = 0;
        for (auto &subject : subjects) {
            subject->applyForce(forces[i++], dt);
        }
    }
}

void Simulation::addSubject(const SimulationSubjectPtr &subject)
{
    subjects.push_back(subject);
}

void Simulation::removeSubject(const SimulationSubjectPtr &subject)
{
    subjects.remove(subject);
}

const std::list<SimulationSubjectPtr> &Simulation::getSubjects() const
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
    std::list<SimulationSubjectPtr> savedObjects = simulationState->getSaved();

    auto iter = subjects.begin();
    while (iter != subjects.end())
    {
        if (simulationState->isSaved(*iter))
        {
            restoreObject(*iter, simulationState);
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
            restoreObject(saved, simulationState);
            addSubject(saved);
        }
    }
}

void Simulation::restoreObject(const SimulationSubjectPtr &obj, SimulationState *simState)
{
    SavableData *savable = simState->getData(obj);
    obj->restore(savable);
    savable->seek(0);
}

unsigned char Simulation::typeID() const
{
    return 1;
}

SavableData *Simulation::save() const
{
    SavableData *savable = Savable::save();
    SavableData *objData;

    for(const auto &subject : subjects)
    {
        objData = subject->save();
        savable->add(*objData);
        delete objData;
    }

    return savable;
}

bool Simulation::restore(SavableData *data)
{
    if(!Savable::restore(data))
        return false;

    clearSubjects();
    while(!data->atEnd())
    {
        SimulationSubjectPtr subject(new SimulationSubject(2));
        subject->restore(data);
        addSubject(subject);
    }

    return true;
}
