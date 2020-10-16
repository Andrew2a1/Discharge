#ifndef CLASSICMODIFICATOR_H
#define CLASSICMODIFICATOR_H

#include "Modificator.h"

class ClassicModificator : public Modificator
{
public:
    virtual std::string name() const override;
    virtual void applyTime(SimulationSubject *subject, RealNumber dt) const override;
    virtual void applyForce(SimulationSubject *subject, const Vector<RealNumber> &force, RealNumber dt) const override;
    virtual void calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const override;
    virtual void collide(SimulationSubject *subject, SimulationSubject *other) override;
};

#endif // CLASSICMODIFICATOR_H
