#include "ElectrostaticForceModificator.h"
#include "physical/SimulationSubject.h"
#include "physical/PhysicalConstants.h"

std::string ElectrostaticForceModificator::name() const
{
    return "ElectrostaticForce";
}

void ElectrostaticForceModificator::calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const
{
    Vector<RealNumber> r = other->getPosition() - subject->getPosition();
    RealNumber distanceCubed = std::pow(r.abs(), 3);

    force += -subject->getElectricCharge() *
            other->getElectricCharge() /
            (4 * PI * e0 * distanceCubed) * r;
}
