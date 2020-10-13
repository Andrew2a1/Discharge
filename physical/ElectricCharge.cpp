#include "ElectricCharge.h"
#include "PhysicalConstants.h"
#include "toolbox/SavableData.h"

ElectricCharge::ElectricCharge(const ElectricCharge &other) :
    PhysicalObject(other),
    charge(other.charge)
{

}

ElectricCharge::ElectricCharge(double mass, double charge) :
    PhysicalObject(mass),
    charge(charge)
{

}

double ElectricCharge::getCharge() const
{
    return charge;
}

void ElectricCharge::setCharge(double charge)
{
    this->charge = charge;
}

Vector<double> ElectricCharge::calculateForce(const PhysicalObject *other) const
{
    Vector<double> force(getPosition().size());
    const ElectricCharge *electrostatic = dynamic_cast<const ElectricCharge*>(other);

    if(electrostatic)
    {
        force = other->getPosition() - getPosition();
        const double distance = force.abs();

        force *= -(getCharge() * electrostatic->getCharge()) /
                 (4 * PI * e0 * std::pow(distance, 3));
    }

    return force + PhysicalObject::calculateForce(other);
}

PhysicalObject *ElectricCharge::clone() const
{
    return new ElectricCharge(*this);
}

unsigned char ElectricCharge::typeID() const
{
    return 3;
}

SavableData *ElectricCharge::save() const 
{
    SavableData *savable = PhysicalObject::save();
    savable->add(RawBytesConst(&charge), sizeof(charge));
    return savable;
}

bool ElectricCharge::restore(SavableData *data)
{
    if(!PhysicalObject::restore(data))
        return false;

    data->read(RawBytes(&charge), sizeof(charge));
    return true;
}
