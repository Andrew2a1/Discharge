#ifndef GRAVITYFORCEMODIFICATOR_H
#define GRAVITYFORCEMODIFICATOR_H

#include "Modificator.h"

class GravityForceModificator : public Modificator
{
public:
    virtual std::string name() const override;
    virtual void calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const override;
};

#endif // GRAVITYFORCEMODIFICATOR_H
