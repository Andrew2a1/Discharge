#include "PhysicalCollisionModificator.h"
#include "physical/SimulationSubject.h"

std::string PhysicalCollisionModificator::name() const
{
    return "PhysicalCollision";
}

void PhysicalCollisionModificator::collide(SimulationSubject *subject, SimulationSubject *other)
{
    Vector<> v1 = (subject->getVelocity()*
                    (subject->getMass() - other->getMass()) +
                    2 * other->getMass()*other->getVelocity()) /
                  (subject->getMass() + other->getMass());

    Vector<> v2 = (other->getVelocity()*
                   (other->getMass() - subject->getMass()) +
                    2 * subject->getMass()*subject->getVelocity()) /
                  (subject->getMass() + other->getMass());

    subject->setVelocity(v1);
    other->setVelocity(v2);

    subject->setPosition(other->getPosition() +
                         (subject->getPosition() -
                          other->getPosition()).normalize() *
                         (subject->getRadius() + other->getRadius())*1.001);
}
