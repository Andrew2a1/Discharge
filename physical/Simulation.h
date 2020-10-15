#ifndef SIMULATION_H
#define SIMULATION_H

#include <list>
#include "SimulationSubjectPtr.h"
#include "toolbox/Savable.h"

#include "RealNumber.h"

class SimulationState;

class Simulation : public Savable
{
private:
    std::list<SimulationSubjectPtr> subjects;

public:
    void applyTime(RealNumber dt);

    void addSubject(const SimulationSubjectPtr &subject);
    void removeSubject(const SimulationSubjectPtr &subject);
    void clearSubjects();

    const std::list<SimulationSubjectPtr>& getSubjects() const;

    SimulationState *saveState() const;
    void restoreState(SimulationState *simulationState);

    virtual unsigned char typeID() const override;
    virtual SavableData* save() const override;
    virtual bool restore(SavableData *data) override;

private:
    void restoreObject(const SimulationSubjectPtr &obj, SimulationState *simState);
};

#endif // SIMULATION_H
