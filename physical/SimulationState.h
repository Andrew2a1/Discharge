#if !defined(SIMULATION_STATE_H)
#define SIMULATION_STATE_H

#include <map>
#include <list>

#include "SimulationSubjectPtr.h"

class SavableData;

class SimulationState
{
private:
    std::map<SimulationSubjectPtr, SavableData*> saved;

public:
    ~SimulationState();

    void saveObject(SimulationSubjectPtr object);
    void removeObject(SimulationSubjectPtr object);
    void clear();

    SavableData* getData(SimulationSubjectPtr object);
    std::list<SimulationSubjectPtr> getSaved() const;
    
    bool isSaved(SimulationSubjectPtr object);
};

#endif // SIMULATION_STATE_H
