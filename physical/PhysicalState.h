#ifndef PHYSICALSTATE_H
#define PHYSICALSTATE_H

#include "toolbox/vector.h"

struct PhysicalState
{
    double mass;
    Vector<double> position;
    Vector<double> velocity;
};

#endif // PHYSICALSTATE_H
