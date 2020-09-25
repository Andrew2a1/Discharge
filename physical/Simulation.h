#ifndef SIMULATION_H
#define SIMULATION_H

#include <list>

class PhysicalObject;
class SimulationState;

class Simulation
{
private:
    std::list<PhysicalObject*> subjects;

public:
    ~Simulation();
    void applyTime(double dt);

    void addSubject(PhysicalObject *subject);
    void removeSubject(PhysicalObject *subject);
    void clearSubjects();
    const std::list<PhysicalObject*> &getSubjects() const; 

    SimulationState *saveState() const;
    void restoreState(SimulationState *simulationState);

private:
    void applyForcesBetween(PhysicalObject *obj, PhysicalObject *other, double dt);
};

#endif // SIMULATION_H