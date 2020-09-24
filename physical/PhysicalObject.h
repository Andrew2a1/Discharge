#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "PhysicalState.h"
#include <list>

class PhysicalMemento;
class PhysicalModifier;

class PhysicalObject
{
private:
    PhysicalState *state = nullptr;
    std::list<PhysicalModifier*> modifiers;

public:
    PhysicalObject(double mass = 1.0);
    virtual ~PhysicalObject();

    double getMass() const;
    const Vector<double> &getPosition() const;
    const Vector<double> &getVelocity() const;

    void setMass(double mass);
    void setPosition(const Vector<double> &position);
    void setVelocity(const Vector<double> &velocity);

    void addModifier(PhysicalModifier *modifier);
    void removeModifier(PhysicalModifier *modifier);
    void clearModifiers();

    void applyTime(double dt);
    void applyForce(const Vector<double> &force, double dt);
    Vector<double> calculateForce(const PhysicalObject *other) const;

    virtual PhysicalMemento *createMemento() const;
    virtual void restoreMemento(const PhysicalMemento *memento);
};

#endif // PHYSICALOBJECT_H
