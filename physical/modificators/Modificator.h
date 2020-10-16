#ifndef MODIFICATOR_H
#define MODIFICATOR_H

#include "toolbox/vector.h"
#include "physical/RealNumber.h"
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
    virtual void applyTime(SimulationSubject *subject, RealNumber dt) const;
    virtual void applyForce(SimulationSubject *subject, const Vector<RealNumber> &force, RealNumber dt) const;
    virtual void calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const;
    virtual void collide(SimulationSubject *subject, SimulationSubject *other);
};

#endif // MODIFICATOR_H
