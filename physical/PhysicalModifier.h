#ifndef PHYSICALMODIFIER_H
#define PHYSICALMODIFIER_H

#include "toolbox/vector.h"

class PhysicalObject;

class PhysicalModifier
{
public:
    virtual ~PhysicalModifier() = default;

    virtual void applyTime(PhysicalObject *physical, double dt) const;

    virtual void applyForce(PhysicalObject *physical,
                            const Vector<double> &force,
                            double dt) const;

    virtual Vector<double> calculateForce(const PhysicalObject *obj,
                                          const PhysicalObject *other) const;
};

#endif // PHYSICALMODIFIER_H
