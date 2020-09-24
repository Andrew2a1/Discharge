#include "PhysicalObject.h"
#include "PhysicalMemento.h"
#include "PhysicalState.h"
#include "PhysicalModifier.h"

PhysicalObject::PhysicalObject(double mass)
{
    state  = new PhysicalState;
    modifier = new PhysicalModifier;

    setMass(mass);
}

PhysicalObject::~PhysicalObject()
{
    delete modifier;
}

double PhysicalObject::getMass() const
{
    return state->mass;
}

const Vector<double> &PhysicalObject::getPosition() const
{
    return state->position;
}

const Vector<double> &PhysicalObject::getVelocity() const
{
    return state->velocity;
}

void PhysicalObject::setMass(double mass)
{
    state->mass = mass;
}

void PhysicalObject::setPosition(const Vector<double> &position)
{
    state->position = position;
}

void PhysicalObject::setVelocity(const Vector<double> &velocity)
{
    state->velocity = velocity;
}

void PhysicalObject::setModifier(PhysicalModifier *modifier)
{
    delete this->modifier;
    this->modifier = modifier;
}

void PhysicalObject::applyTime(double dt)
{
    modifier->applyTime(this, dt);
}

void PhysicalObject::applyForce(const Vector<double> &force, double dt)
{
    modifier->applyForce(this, force, dt);
}

Vector<double> PhysicalObject::calculateForce(const PhysicalObject *other) const
{
    return modifier->calculateForce(this, other);
}

PhysicalMemento *PhysicalObject::createMemento() const
{
    PhysicalMemento *memento = new PhysicalMemento();
    PhysicalState *current = new PhysicalState(*state);

    memento->setState(current);
    return memento;
}

void PhysicalObject::restoreMemento(const PhysicalMemento *memento)
{
    state = memento->getState();
}
