#include "SimulationState.h"
#include "physical/SimulationSubject.h"
#include "toolbox/SavableData.h"

SimulationState::~SimulationState()
{
    clear();
}

void SimulationState::clear()
{
    for(const auto &item : saved)
        delete saved[item.first];

    saved.clear();
}

void SimulationState::saveObject(SimulationSubjectPtr object)
{
    saved[object] = object->save();
}

void SimulationState::removeObject(SimulationSubjectPtr object)
{
    delete saved[object];
    saved.erase(object);
}

SavableData *SimulationState::getData(SimulationSubjectPtr object)
{
    return saved[object];
}

std::list<SimulationSubjectPtr> SimulationState::getSaved() const
{
    std::list<SimulationSubjectPtr> objects;

    for(const auto &key : saved)
        objects.push_back(key.first);

    return objects;
}

bool SimulationState::isSaved(SimulationSubjectPtr object)
{
    return saved.find(object) != saved.end();
}
