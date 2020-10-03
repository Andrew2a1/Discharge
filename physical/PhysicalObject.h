#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "toolbox/vector.h"
#include "toolbox/Savable.h"

class PhysicalObject : public Savable
{
private:
    double mass;
    Vector<double> position;
    Vector<double> velocity;

public:
    PhysicalObject(double mass = 1.0);
    virtual ~PhysicalObject() = default;

    double getMass() const;
    const Vector<double> &getPosition() const;
    const Vector<double> &getVelocity() const;

    void setMass(double mass);
    void setPosition(const Vector<double> &position);
    void setVelocity(const Vector<double> &velocity);

    virtual void applyTime(double dt);
    virtual void applyForce(const Vector<double> &force, double dt);
    virtual Vector<double> calculateForce(const PhysicalObject *other) const;

    virtual SavableData* save() const override;
    virtual unsigned restore(const SavableData *data) override;
};

#endif // PHYSICALOBJECT_H
