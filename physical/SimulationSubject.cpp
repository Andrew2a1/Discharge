#include "SimulationSubject.h"
#include "toolbox/SavableData.h"
#include "ModificatorFactory.h"

SimulationSubject::SimulationSubject(unsigned dimensions, const RealNumber &radius) :
    position(Vector<RealNumber>(dimensions)),
    velocity(Vector<RealNumber>(dimensions)),
    radius(radius),
    dimensions(dimensions)
{

}

SimulationSubject::SimulationSubject(unsigned dimensions,
                                     RealNumber radius,
                                     RealNumber mass,
                                     RealNumber electricCharge) :
    SimulationSubject(dimensions, radius)
{
    this->mass = mass;
    this->electricCharge = electricCharge;
}

Vector<RealNumber> SimulationSubject::getPosition() const
{
    return position;
}

void SimulationSubject::setPosition(const Vector<RealNumber> &value)
{
    position = value;
}

Vector<RealNumber> SimulationSubject::getVelocity() const
{
    return velocity;
}

void SimulationSubject::setVelocity(const Vector<RealNumber> &value)
{
    velocity = value;
}

RealNumber SimulationSubject::getMass() const
{
    return mass;
}

void SimulationSubject::setMass(const RealNumber &value)
{
    mass = value;
}

RealNumber SimulationSubject::getElectricCharge() const
{
    return electricCharge;
}

void SimulationSubject::setElectricCharge(const RealNumber &value)
{
    electricCharge = value;
}

RealNumber SimulationSubject::getRadius() const
{
    return radius;
}

void SimulationSubject::setRadius(const RealNumber &value)
{
    radius = value;
}

unsigned SimulationSubject::getDimensions() const
{
    return dimensions;
}

void SimulationSubject::applyTime(RealNumber dt)
{
    for(const auto &modificator: modificators)
    {
        modificator->applyTime(this, dt);
    }
}

void SimulationSubject::applyForce(const Vector<RealNumber> &force, RealNumber dt)
{
    for(const auto &modificator: modificators)
    {
        modificator->applyForce(this, force, dt);
    }
}

Vector<RealNumber> SimulationSubject::calculateForce(const SimulationSubject *other) const
{
    Vector<RealNumber> force(dimensions);
    for(const auto &modificator: modificators)
    {
        modificator->calculateForce(this, other, force);
    }

    return force;
}


unsigned char SimulationSubject::typeID() const
{
    return 2;
}

SavableData *SimulationSubject::save() const
{
    SavableData *savable = Savable::save();

    savable->add(RawBytesConst(&mass), sizeof(mass));
    savable->add(RawBytesConst(&electricCharge), sizeof(electricCharge));
    savable->add(RawBytesConst(&radius), sizeof(radius));
    savable->add(RawBytesConst(&dimensions), sizeof(dimensions));
    saveVector(position, savable);
    saveVector(velocity, savable);

    savable->add(modificators.size());

    for(const auto &modificator: modificators)
        saveModificator(modificator, savable);

    return savable;
}

void SimulationSubject::saveVector(const Vector<RealNumber> &vect, SavableData *savable) const
{
    savable->add(vect.size());

    for(int i = 0; i < vect.size(); ++i)
        savable->add(RawBytesConst(&(vect[i])), sizeof(RealNumber));
}

bool SimulationSubject::restore(SavableData *data)
{
    if(!Savable::restore(data))
        return false;

    data->read(RawBytes(&mass), sizeof(mass));
    data->read(RawBytes(&electricCharge), sizeof(electricCharge));
    data->read(RawBytes(&radius), sizeof(radius));
    data->read(RawBytes(&dimensions), sizeof(dimensions));

    position = restoreVector(data);
    velocity = restoreVector(data);

    modificators.clear();

    int size = data->read();
    for(int i = 0; i < size; ++i)
        modificators.push_back(restoreModificator(data));

    return true;
}

void SimulationSubject::saveModificator(const Modificator *modificator, SavableData *savable) const
{
    std::string name = modificator->name();

    savable->add(name.size());
    savable->add(RawBytesConst(name.data()), name.size());
}

Modificator *SimulationSubject::restoreModificator(SavableData *savable)
{
    Modificator *modificator;
    ModificatorFactory *factory = ModificatorFactory::instance();

    int size = savable->read();
    char *name = new char[size];

    modificator = factory->get(name);

    delete[] name;
    return modificator;
}

Vector<RealNumber> SimulationSubject::restoreVector(SavableData *savable) const
{
    Vector<RealNumber> result(savable->read());

    for(int i = 0; i < velocity.size(); ++i)
        savable->read(RawBytes(&(result[i])), sizeof(RealNumber));

    return result;
}



