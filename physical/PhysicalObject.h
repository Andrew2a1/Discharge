#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "PhysicalState.h"

class PhysicalMemento;

class PhysicalObject
{
private:
    PhysicalState state;

public:
    PhysicalObject(double mass = 1.0);

    double getMass() const;
    const Vector<double> &getPosition() const;
    const Vector<double> &getVelocity() const;

    void setMass(double mass);
    void setPosition(const Vector<double> &position);
    void setVelocity(const Vector<double> &velocity);

    virtual PhysicalMemento *createMemento() const;
    virtual void restoreMemento(const PhysicalMemento *memento);
};

#endif // PHYSICALOBJECT_H
