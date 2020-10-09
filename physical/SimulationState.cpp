#include "SimulationState.h"
#include "PhysicalObject.h"
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

void SimulationState::saveObject(PhysicalObjectPtr object)
{
    saved[object] = object->save();
}

void SimulationState::removeObject(PhysicalObjectPtr object)
{
    delete saved[object];
    saved.erase(object);
}

SavableData *SimulationState::getData(PhysicalObjectPtr object)
{
    return saved[object];
}

std::list<PhysicalObjectPtr> SimulationState::getSaved() const
{
    std::list<PhysicalObjectPtr> objects;

    for(const auto &key : saved)
        objects.push_back(key.first);

    return objects;
}

bool SimulationState::isSaved(PhysicalObjectPtr object)
{
    return saved.find(object) != saved.end();
}
