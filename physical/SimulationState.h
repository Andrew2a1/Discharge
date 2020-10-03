#if !defined(SIMULATION_STATE_H)
#define SIMULATION_STATE_H

#include <list>

class PhysicalMemento;
class PhysicalObject;
class Simulation;

struct ObjectMemento {
    PhysicalObject *object;
    PhysicalMemento *memento;
};

class SimulationState
{
private:
    std::list<ObjectMemento*> mementos;

public:
    SimulationState(const std::list<PhysicalObject*> &subjects);
    ~SimulationState();

    void addMementoFrom(PhysicalObject *object);
    void removeMemento(PhysicalObject *object);
    void clear();

    void restoreState(Simulation *simulation);

private:
    bool containsPhysical(const std::list<PhysicalObject *> &objects,
                          const PhysicalObject* physical) const;

    bool isObjectInMementos(const PhysicalObject* physical) const;
};

#endif // SIMULATION_STATE_H
