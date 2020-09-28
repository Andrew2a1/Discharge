#include "PhysicalObject.h"
#include "PhysicalMemento.h"
#include "PhysicalState.h"
#include "PhysicalModifier.h"

PhysicalObject::PhysicalObject(const PhysicalObject &other) :
    PhysicalObject(other.getMass())
{
    setPosition(other.getPosition());
    setVelocity(other.getVelocity());
}

PhysicalObject::PhysicalObject(double mass)
{
    state = new PhysicalState;
    addModifier(new PhysicalModifier);
    setMass(mass);
}

PhysicalObject::~PhysicalObject()
{
    delete state;
    clearModifiers();
}

void PhysicalObject::clearModifiers()
{
    for(auto &modifier: modifiers)
        delete modifier;

    modifiers.clear();
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

void PhysicalObject::addModifier(PhysicalModifier *modifier)
{
    modifiers.push_back(modifier);
}

void PhysicalObject::removeModifier(PhysicalModifier *modifier)
{
    modifiers.remove(modifier);
}

void PhysicalObject::applyTime(double dt)
{
    for(auto &modifier: modifiers)
        modifier->applyTime(this, dt);
}

void PhysicalObject::applyForce(const Vector<double> &force, double dt)
{
    for(auto &modifier: modifiers)
        modifier->applyForce(this, force, dt);
}

Vector<double> PhysicalObject::calculateForce(const PhysicalObject *other) const
{
    Vector<double> force(getPosition().size());

    for(auto &modifier: modifiers)
        force += modifier->calculateForce(this, other);

    return force;
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
    *state = *memento->getState();
}
