#ifndef SIMULATION_H
#define SIMULATION_H

#include <list>
#include "PhysicalObjectPtr.h"

class SimulationState;

class Simulation
{
private:
    std::list<PhysicalObjectPtr> subjects;

public:
    void applyTime(double dt);

    void addSubject(PhysicalObjectPtr subject);
    void removeSubject(PhysicalObjectPtr subject);
    void clearSubjects();

    const std::list<PhysicalObjectPtr>& getSubjects() const;

    SimulationState *saveState() const;
    void restoreState(SimulationState *simulationState);
};

#endif // SIMULATION_H
