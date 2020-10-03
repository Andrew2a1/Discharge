#ifndef SIMULATION_H
#define SIMULATION_H

#include <list>
#include "PhysicalObjectPtr.h"

class PhysicalObject;
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

    SimulationState *saveState() const;
    void restoreState(SimulationState *simulationState);

private:
    void applyForcesBetween(PhysicalObjectPtr obj, PhysicalObjectPtr other, double dt);
};

#endif // SIMULATION_H