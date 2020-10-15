#ifndef PHYSICALCOLLISIONMODIFICATOR_H
#define PHYSICALCOLLISIONMODIFICATOR_H

#include "Modificator.h"

class PhysicalCollisionModificator : public Modificator
{
public:
    virtual std::string name() const override;
    virtual void collide(SimulationSubject *subject, SimulationSubject *other) override;
};

#endif // PHYSICALCOLLISIONMODIFICATOR_H
