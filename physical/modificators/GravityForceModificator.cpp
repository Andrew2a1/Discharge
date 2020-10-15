#include "GravityForceModificator.h"
#include "physical/SimulationSubject.h"
#include "physical/PhysicalConstants.h"

std::string GravityForceModificator::name() const
{
    return "GravityForce";
}

void GravityForceModificator::calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const
{
    Vector<RealNumber> r = other->getPosition() - subject->getPosition();
    RealNumber distanceCubed = std::pow(r.abs(), 3);

    force += (subject->getMass() *
            other->getMass() * G /
            distanceCubed) * r;
}
