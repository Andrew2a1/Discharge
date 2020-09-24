#ifndef CHARGEMODIFIER_H
#define CHARGEMODIFIER_H

#include "PhysicalModifier.h"

class ChargeModifier : public PhysicalModifier
{
public:
    virtual Vector<double> calculateForce(const PhysicalObject *obj,
                                          const PhysicalObject *other) const;
};

#endif // CHARGEMODIFIER_H
