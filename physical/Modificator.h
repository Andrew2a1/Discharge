#ifndef MODIFICATOR_H
#define MODIFICATOR_H

#include "toolbox/vector.h"
#include "RealNumber.h"
#include <string>

class ModificatorFactory;
class SimulationSubject;

class Modificator
{
    friend class ModificatorFactory;

protected:
    Modificator() = default;
    virtual ~Modificator() = default;

public:
    virtual std::string name() const = 0;
    virtual void applyTime(SimulationSubject *subject, RealNumber dt) const = 0;
    virtual void applyForce(SimulationSubject *subject, const Vector<RealNumber> &force, RealNumber dt) const = 0;
    virtual void calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const = 0;
};

#endif // MODIFICATOR_H
