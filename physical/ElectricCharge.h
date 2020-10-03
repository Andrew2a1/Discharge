#ifndef ELECTRICCHARGE_H
#define ELECTRICCHARGE_H

#include "PhysicalObject.h"

class ElectricCharge : public PhysicalObject
{
    double charge;

public:
    ElectricCharge(double mass = 1.0, double charge = 1.0);
    virtual ~ElectricCharge() = default;

    double getCharge() const;
    void setCharge(double charge);

    virtual Vector<double> calculateForce(const PhysicalObject *other) const override;
};

#endif // ELECTRICCHARGE_H
