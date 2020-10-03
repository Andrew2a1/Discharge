#include "PhysicalObject.h"
#include "PhysicalConstants.h"
#include "SavableData.h"

#include <cstring>

PhysicalObject::PhysicalObject(double mass) :
    mass(mass)
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

SavableData *PhysicalObject::save() const
{
    const unsigned total = sizeof(mass) + sizeof(position) + sizeof(velocity);
    SavableData *savable = new SavableData(total);
    Vector<double> *vect;

    savable->add(PackObject(mass));

    vect = new Vector<double>(position);
    savable->add(PackObjectPtr(vect));

    vect = new Vector<double>(velocity);
    savable->add(PackObjectPtr(vect));

    return savable;
}

unsigned PhysicalObject::restore(const SavableData *data)
{
    unsigned offset = 0;
    const Vector<double> *vect;

    std::memcpy(&mass, data->getRaw(), sizeof(mass));
    offset += sizeof(mass);

    vect = (const Vector<double> *)(data->getRaw(offset));
    position = std::move(*vect);
    offset += sizeof(position);

    vect = (const Vector<double> *)(data->getRaw(offset));
    velocity = std::move(*vect);
    offset += sizeof(velocity);

    return offset;
}