#ifndef FORCESENSITIVEMODIFICATOR_H
#define FORCESENSITIVEMODIFICATOR_H

#include "Modificator.h"

class ForceSensitiveModificator : public Modificator
{
public:
    virtual std::string name() const override;
    virtual void applyForce(SimulationSubject *subject, const Vector<RealNumber> &force, RealNumber dt) const override;
};

#endif // FORCESENSITIVEMODIFICATOR_H
