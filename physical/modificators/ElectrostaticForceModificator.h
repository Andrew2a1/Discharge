#ifndef ELECTROSTATICFORCEMODIFICATOR_H
#define ELECTROSTATICFORCEMODIFICATOR_H

#include "Modificator.h"

class ElectrostaticForceModificator : public Modificator
{
public:
    virtual std::string name() const override;
    virtual void calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const override;

};

#endif // ELECTROSTATICFORCEMODIFICATOR_H
