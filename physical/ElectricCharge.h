#ifndef ELECTRICCHARGE_H
#define ELECTRICCHARGE_H

#include "PhysicalObject.h"

class ElectricCharge : public PhysicalObject
{
    double charge;

public:
    ElectricCharge(double charge = 1.0, double mass = 1.0);
    virtual ~ElectricCharge() = default;

    double getCharge() const;
    void setCharge(double charge);

    virtual PhysicalMemento *createMemento() const;
    virtual void restoreMemento(const PhysicalMemento *memento);
};

#endif // ELECTRICCHARGE_H
