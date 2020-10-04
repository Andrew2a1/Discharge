#if !defined(SIMULATION_STATE_H)
#define SIMULATION_STATE_H

#include <map>
#include <list>

#include "PhysicalObjectPtr.h"

class SavableData;

class SimulationState
{
private:
    std::map<PhysicalObjectPtr, SavableData*> saved;

public:
    ~SimulationState();

    void saveObject(PhysicalObjectPtr object);
    void removeObject(PhysicalObjectPtr object);
    void clear();

    SavableData* getData(PhysicalObjectPtr object);
    std::list<PhysicalObjectPtr> getSaved() const;
    
    bool isSaved(PhysicalObjectPtr object);
};

#endif // SIMULATION_STATE_H
