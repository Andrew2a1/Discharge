#include "Modificator.h"
#include "toolbox/Unused.h"

void Modificator::applyTime(SimulationSubject *subject,
                            RealNumber dt) const
{
    UNUSED(subject);
    UNUSED(dt);
}

void Modificator::applyForce(SimulationSubject *subject,
                             const Vector<RealNumber> &force,
                             RealNumber dt) const
{
    UNUSED(subject);
    UNUSED(force);
    UNUSED(dt);
}

void Modificator::calculateForce(const SimulationSubject *subject,
                                 const SimulationSubject *other,
                                 Vector<RealNumber> &force) const
{
    UNUSED(subject);
    UNUSED(other);
    UNUSED(force);
}

void Modificator::collide(SimulationSubject *subject,
                          SimulationSubject *other)
{
    UNUSED(subject);
    UNUSED(other);
}
