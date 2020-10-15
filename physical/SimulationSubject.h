#ifndef SIMULATIONSUBJECT_H
#define SIMULATIONSUBJECT_H

#include "toolbox/Savable.h"
#include "Modificator.h"
#include "RealNumber.h"
#include "toolbox/vector.h"

#include <list>

class SimulationSubject : public Savable
{
    std::list<Modificator*> modificators;
    Vector<RealNumber> position;
    Vector<RealNumber> velocity;

    RealNumber mass = 1;
    RealNumber electricCharge = 0;

    RealNumber radius = 1;
    unsigned dimensions = 3;

public:
    SimulationSubject(unsigned dimensions = 3, const RealNumber &radius = 1);

    SimulationSubject(unsigned dimensions,
                      RealNumber radius,
                      RealNumber mass,
                      RealNumber electricCharge = 0);

    void addModificator(Modificator *modificator);
    void removeModificator(Modificator *modificator);
    const std::list<Modificator *> &getModificators() const;

    int getModificatorIndex(Modificator *modificator);
    void swapModificators(Modificator *first, Modificator *second);

    unsigned getDimensions() const;
    RealNumber getRadius() const;
    RealNumber getMass() const;
    RealNumber getElectricCharge() const;
    Vector<RealNumber> getPosition() const;
    Vector<RealNumber> getVelocity() const;

    void setRadius(const RealNumber &value);
    void setMass(const RealNumber &value);
    void setElectricCharge(const RealNumber &value);
    void setPosition(const Vector<RealNumber> &value);
    void setVelocity(const Vector<RealNumber> &value);

    void applyTime(RealNumber dt);
    void applyForce(const Vector<RealNumber> &force, RealNumber dt);
    Vector<RealNumber> calculateForce(const SimulationSubject *other) const;
    void collide(SimulationSubject *other);

    bool isCollision(const SimulationSubject *other);

    virtual unsigned char typeID() const override;
    virtual SavableData* save() const override;
    virtual bool restore(SavableData *data) override;


private:
    void saveModificator(const Modificator* modificator, SavableData *savable) const;
    Modificator *restoreModificator(SavableData *savable);

    void saveVector(const Vector<RealNumber> &vect, SavableData *savable) const;
    Vector<RealNumber> restoreVector(SavableData *savable) const;
};

#endif // SIMULATIONSUBJECT_H
