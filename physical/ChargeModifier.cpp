#include "ChargeModifier.h"
#include "ElectricCharge.h"

#include <cmath>

constexpr double e0 = 8.84e-12;
constexpr double PI = 3.14159265359;

Vector<double> ChargeModifier::calculateForce(const PhysicalObject *obj, const PhysicalObject *other) const
{
    const ElectricCharge *charge1 = dynamic_cast<const ElectricCharge*>(obj);
    const ElectricCharge *charge2 = dynamic_cast<const ElectricCharge*>(other);
    Vector<double> force(obj->getPosition().size());

    if(charge1 && charge2)
    {
        force = obj->getPosition() - other->getPosition();
        const double distance = force.abs();

        force *= charge1->getCharge() * charge2->getCharge() /
                    (4*PI*e0 * std::pow(distance, 3));
    }

    return force;
}
