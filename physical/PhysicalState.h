#ifndef PHYSICALSTATE_H
#define PHYSICALSTATE_H

#include "toolbox/vector.h"

class PhysicalState
{
public:
    virtual ~PhysicalState() = default;

    double mass;
    Vector<double> position;
    Vector<double> velocity;
};

#endif // PHYSICALSTATE_H
