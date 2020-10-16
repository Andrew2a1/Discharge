#include "ChargeExchangeModificator.h"
#include "physical/SimulationSubject.h"

std::string ChargeExchangeModificator::name() const
{
    return "ChargeExchange";
}

void ChargeExchangeModificator::collide(SimulationSubject *subject, SimulationSubject *other)
{
    RealNumber charge = subject->getElectricCharge() + other->getElectricCharge();
    subject->setElectricCharge(charge / 2);
    other->setElectricCharge(charge / 2);
}
