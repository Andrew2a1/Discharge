#include "PhysicalObject.h"
#include "PhysicalMemento.h"
#include "PhysicalState.h"

PhysicalObject::PhysicalObject(double mass)
{
    state = {mass, Vector<double>(2), Vector<double>(2)};
}

double PhysicalObject::getMass() const
{
    return state.mass;
}

const Vector<double> &PhysicalObject::getPosition() const
{
    return state.position;
}

const Vector<double> &PhysicalObject::getVelocity() const
{
    return state.velocity;
}

void PhysicalObject::setMass(double mass)
{
    state.mass = mass;
}

void PhysicalObject::setPosition(const Vector<double> &position)
{
    state.position = position;
}

void PhysicalObject::setVelocity(const Vector<double> &velocity)
{
   state.velocity = velocity;
}

PhysicalMemento *PhysicalObject::createMemento() const
{
    PhysicalMemento *memento = new PhysicalMemento();
    PhysicalState *current = new PhysicalState(state);

    memento->setState(current);
    return memento;
}

void PhysicalObject::restoreMemento(const PhysicalMemento *memento)
{
    PhysicalState* old = memento->getState();
    state = *old;
}
