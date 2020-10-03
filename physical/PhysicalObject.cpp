#include "PhysicalObject.h"
#include "PhysicalConstants.h"

PhysicalObject::PhysicalObject(double mass) :
    mass(mass)
{

}

PhysicalObject::~PhysicalObject()
{
    
}

double PhysicalObject::getMass() const
{
    return this->mass;
}

const Vector<double> &PhysicalObject::getPosition() const
{
    return this->position;
}

const Vector<double> &PhysicalObject::getVelocity() const
{
    return this->velocity;
}

void PhysicalObject::setMass(double mass)
{
    this->mass = mass;
}

void PhysicalObject::setPosition(const Vector<double> &position)
{
    this->position = position;
}

void PhysicalObject::setVelocity(const Vector<double> &velocity)
{
    this->velocity = velocity;
}

void PhysicalObject::applyTime(double dt)
{
    Vector<double> pos = getPosition();
    pos += getVelocity() * dt;
    setPosition(pos);
}

void PhysicalObject::applyForce(const Vector<double> &force, double dt)
{
    Vector<double> v = getVelocity();
    Vector<double> s = getPosition();
    const Vector<double> dv = force / getMass() *dt;

    s += v*dt + dv*dt/2;
    v += dv;

    setPosition(s);
    setVelocity(v);
}

Vector<double> PhysicalObject::calculateForce(const PhysicalObject *other) const
{
    Vector<double> force = other->getPosition() - getPosition();
    double distance = force.abs();

    force *= getMass() * other->getMass() * G / std::pow(distance, 3);
    return force;
}
