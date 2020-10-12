#ifndef SIMULATION_H
#define SIMULATION_H

#include <list>
#include "PhysicalObjectPtr.h"
#include "toolbox/Savable.h"

class SimulationState;

class Simulation : public Savable
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

    virtual unsigned char typeID() const override;
    virtual SavableData* save() const override;
    virtual bool restore(SavableData *data) override;

private:
    void restoreObject(const PhysicalObjectPtr &obj, SimulationState *simState);
};

#endif // SIMULATION_H
