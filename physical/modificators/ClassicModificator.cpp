#include "ClassicModificator.h"
#include "physical/SimulationSubject.h"
#include "physical/PhysicalConstants.h"

std::string ClassicModificator::name() const
{
    return "AllInOne";
}

void ClassicModificator::applyTime(SimulationSubject *subject, RealNumber dt) const
{
    Vector<RealNumber> pos = subject->getPosition();
    pos += subject->getVelocity() * dt;
    subject->setPosition(pos);
}

void ClassicModificator::applyForce(SimulationSubject *subject, const Vector<RealNumber> &force, RealNumber dt) const
{
    Vector<RealNumber> v = subject->getVelocity();
    Vector<RealNumber> s = subject->getPosition();
    const Vector<RealNumber> dv = force / subject->getMass() *dt;

    s += v*dt + dv*dt/2;
    v += dv;

    subject->setPosition(s);
    subject->setVelocity(v);
}

void ClassicModificator::calculateForce(const SimulationSubject *subject, const SimulationSubject *other, Vector<RealNumber> &force) const
{
    Vector<RealNumber> r = other->getPosition() - subject->getPosition();
    RealNumber distanceCubed = std::pow(r.abs(), 3);

    Vector<RealNumber> gravityForce = subject->getMass() *
                                        other->getMass() * G /
                                        distanceCubed * r;

    Vector<RealNumber> electrostaticForce = -subject->getElectricCharge() *
                                             other->getElectricCharge() /
                                             (4 * PI * e0 * distanceCubed) * r;

    force += gravityForce + electrostaticForce;
}

void ClassicModificator::collide(SimulationSubject *subject, SimulationSubject *other)
{
    RealNumber charge = subject->getElectricCharge() + other->getElectricCharge();
    subject->setElectricCharge(charge / 2);
    other->setElectricCharge(charge / 2);

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
