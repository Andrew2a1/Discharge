#ifndef PHYSICALSTATE_H
#define PHYSICALSTATE_H

#include "toolbox/vector.h"

class PhysicalState
{
public:
    virtual ~PhysicalState() = default;
    PhysicalState() = default;

    PhysicalState(double mass,
                  const Vector<double> &position,
                  const Vector<double> &velocity) :
        mass(mass),
        position(position),
        velocity(velocity)
    {

    }

    double mass;
    Vector<double> position;
    Vector<double> velocity;
};

#endif // PHYSICALSTATE_H
