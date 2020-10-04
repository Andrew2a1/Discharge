#include "PhysicalObject.h"
#include "PhysicalConstants.h"
#include "toolbox/SavableData.h"

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

    savable->add(PackObject(mass));
    saveVector(position, savable);
    saveVector(velocity, savable);

    return savable;
}

unsigned PhysicalObject::restore(const SavableData *data)
{
    unsigned offset = 0;

    std::memcpy(&mass, data->getRaw(), sizeof(mass));
    offset += sizeof(mass);

    position = restoreVector(data, offset);
    velocity = restoreVector(data, offset);
    return offset;
}

void PhysicalObject::saveVector(const Vector<double> &vect, SavableData *savable) const
{
    savable->add(vect.size());

    for(int i = 0; i < vect.size(); ++i)
        savable->add(PackObject(vect[i]));
}

Vector<double> PhysicalObject::restoreVector(const SavableData *savable, unsigned &offset) const
{
    Vector<double> result(*savable->getRaw(offset));
    offset += 1;

    for(int i = 0; i < velocity.size(); ++i)
    {
        result[i] = *(double*)(savable->getRaw(offset));
        offset += sizeof(double);
    }

    return result;
}
