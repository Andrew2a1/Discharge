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

Simulation::Simulation() :
    threadPool(4)
{

}

void Simulation::applyTime(RealNumber dt)
{
    if (subjects.size() == 1)
    {
        subjects.front()->applyTime(dt);
    }
    else if (subjects.size() > 1)
    {
        std::vector<Vector<double>> forces = calculateAllForces();

        int i = 0;
        for (auto &subject : subjects)
        {
            for (auto &other : subjects)
            {
                if (subject != other && subject->isCollision(other.get()))
                    subject->collide(other.get());
            }

            subject->applyForce(forces[i++], dt);
        }
    }
}

std::vector<Vector<double>> Simulation::calculateAllForces()
{
    const Vector<double> vectZero = Vector<double>(subjects.front()->getDimensions());
    std::vector<Vector<double>> forces(subjects.size(), vectZero);
    std::list<std::future<void>> futures;

    const int minForTask = std::fmax(10, subjects.size()/threadPool.threadCount());
    const int tasks = subjects.size() / minForTask;

    auto blockStart = subjects.begin();
    auto outBlockStart = forces.begin();
    for(int i = 0; i < tasks - 1; ++i)
    {
        auto blockEnd = blockStart;
        std::advance(blockEnd, minForTask);

        futures.push_back(threadPool.submit([=](){
            partialCalculate(blockStart,
                              blockEnd,
                              outBlockStart);
        }));

        std::advance(outBlockStart, minForTask);
        blockStart = blockEnd;
    }

    partialCalculate(blockStart, subjects.end(), outBlockStart);

    for(const auto &future : futures)
        future.wait();

    return forces;
}

Vector<double> Simulation::calculateForce(const SimulationSubjectPtr &subject) const
{
    Vector<double> force(subject->getDimensions());

    for (auto &other : subjects)
    {
        if (subject != other)
        {
            force += subject->calculateForce(other.get());
        }
    }

    return force;
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
