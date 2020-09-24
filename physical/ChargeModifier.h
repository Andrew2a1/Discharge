#ifndef CHARGEMODIFIER_H
#define CHARGEMODIFIER_H

#include "PhysicalModifier.h"

class ChargeModifier : public PhysicalModifier
{
public:
    virtual ~ChargeModifier() = default;

    virtual void applyTime(PhysicalObject *physical, double dt) const;

    virtual void applyForce(PhysicalObject *physical,
                            const Vector<double> &force,
                            double dt) const;

    virtual Vector<double> calculateForce(const PhysicalObject *obj,
                                          const PhysicalObject *other) const;
};

#endif // CHARGEMODIFIER_H
