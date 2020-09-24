#include "PhysicalModifier.h"
#include "PhysicalObject.h"

constexpr double G = 6.6743e-11;

void PhysicalModifier::applyTime(PhysicalObject *physical, double dt) const
{
    Vector<double> pos = physical->getPosition();
    pos += physical->getVelocity() * dt;
    physical->setPosition(pos);
}

void PhysicalModifier::applyForce(PhysicalObject *physical,
                                  const Vector<double> &force,
                                  double dt) const
{
    Vector<double> v = physical->getVelocity();
    Vector<double> s = physical->getPosition();
    const Vector<double> dv = force / physical->getMass() *dt;

    s += v*dt + dv*dt/2;
    v += dv;

    physical->setPosition(s);
    physical->setVelocity(v);
}

Vector<double> PhysicalModifier::calculateForce(const PhysicalObject *obj,
                                                const PhysicalObject *other) const
{
    Vector<double> force = other->getPosition() - obj->getPosition();
    double distance = force.abs();

    force *= obj->getMass() * other->getMass() * G / std::pow(distance, 3);
    return force;
}
