#ifndef SIMULATION_H
#define SIMULATION_H

#include <list>
#include "SimulationSubjectPtr.h"
#include "toolbox/Savable.h"

#include "RealNumber.h"
#include "toolbox/vector.h"

#include "toolbox/ThreadPool.h"

class SimulationState;

class Simulation : public Savable
{
private:
    ThreadPool threadPool;
    std::list<SimulationSubjectPtr> subjects;

public:
    Simulation();
    virtual ~Simulation() = default;

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

    std::vector<Vector<double>> calculateAllForces();
    Vector<double> calculateForce(const SimulationSubjectPtr &subject) const;

    template <typename InIterator, typename OutIterator>
    void partialCalculate(InIterator first, InIterator last, OutIterator output) const {
        InIterator current = first;
        while(current != last)
        {
            *output = calculateForce(*current);
            ++current;
            ++output;
        }
    }
};

#endif // SIMULATION_H
