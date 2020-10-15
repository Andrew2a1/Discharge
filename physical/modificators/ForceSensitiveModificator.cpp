#include "ForceSensitiveModificator.h"
#include "physical/SimulationSubject.h"
#include "physical/PhysicalConstants.h"

std::string ForceSensitiveModificator::name() const
{
    return "ForceSensitive";
}

void ForceSensitiveModificator::applyForce(SimulationSubject *subject, const Vector<RealNumber> &force, RealNumber dt) const
{
    Vector<RealNumber> v = subject->getVelocity();
    Vector<RealNumber> s = subject->getPosition();
    const Vector<RealNumber> dv = force / subject->getMass() *dt;

    s += v*dt + dv*dt/2;
    v += dv;

    subject->setPosition(s);
    subject->setVelocity(v);
}
