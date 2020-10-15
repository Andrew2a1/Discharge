#include "MovableModificator.h"
#include "physical/SimulationSubject.h"
#include "physical/PhysicalConstants.h"

std::string MovableModificator::name() const
{
    return "Movable";
}

void MovableModificator::applyTime(SimulationSubject *subject, RealNumber dt) const
{
    Vector<RealNumber> pos = subject->getPosition();
    pos += subject->getVelocity() * dt;
    subject->setPosition(pos);
}
