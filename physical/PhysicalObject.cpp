#include "PhysicalObject.h"
#include "PhysicalConstants.h"
#include "toolbox/SavableData.h"

#include <cstring>

PhysicalObject::PhysicalObject(const PhysicalObject &other) :
    mass(other.mass),
    position(other.position),
    velocity(other.velocity)
{

}

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

PhysicalObject *PhysicalObject::clone() const
{
    return new PhysicalObject(*this);
}

unsigned char PhysicalObject::typeID() const
{
    return 2;
}

SavableData *PhysicalObject::save() const
{
    const unsigned total = sizeof(mass) + sizeof(position) + sizeof(velocity);

    SavableData *savable = Savable::save();
    savable->reserve(savable->size() + total);

    savable->add(RawBytesConst(&mass), sizeof(mass));
    saveVector(position, savable);
    saveVector(velocity, savable);

    return savable;
}

void PhysicalObject::saveVector(const Vector<double> &vect, SavableData *savable) const
{
    savable->add(vect.size());

    for(int i = 0; i < vect.size(); ++i)
        savable->add(RawBytesConst(&(vect[i])), sizeof(double));
}

bool PhysicalObject::restore(SavableData *data)
{
    if(!Savable::restore(data))
        return false;

    data->read(RawBytes(&mass), sizeof(mass));

    position = restoreVector(data);
    velocity = restoreVector(data);

    return true;
}

Vector<double> PhysicalObject::restoreVector(SavableData *savable) const
{
    Vector<double> result(savable->read());

    for(int i = 0; i < velocity.size(); ++i)
        savable->read(RawBytes(&(result[i])), sizeof(double));

    return result;
}
