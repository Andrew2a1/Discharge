#if !defined(SIMULATION_STATE_H)
#define SIMULATION_STATE_H

#include <list>

class PhysicalMemento;
class PhysicalObject;

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
    void restoreState();
};

#endif // SIMULATION_STATE_H
