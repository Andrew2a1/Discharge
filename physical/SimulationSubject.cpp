#include "SimulationSubject.h"
#include "modificators/ModificatorFactory.h"
#include "toolbox/SavableData.h"
#include "toolbox/Unused.h"

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

void SimulationSubject::addModificator(Modificator *modificator)
{
    if(modificator != nullptr)
        modificators.push_back(modificator);
}

void SimulationSubject::addModificator(const std::string &name)
{
    ModificatorFactory *factory = ModificatorFactory::instance();

    if(factory->hasItem(name))
        modificators.push_back(factory->get(name));
}

void SimulationSubject::removeModificator(Modificator *modificator)
{
    modificators.remove(modificator);
}

void SimulationSubject::setModificators(const std::list<Modificator *> &value)
{
    modificators = value;
}

const std::list<Modificator*> &SimulationSubject::getModificators() const
{
    return modificators;
}

int SimulationSubject::getModificatorIndex(Modificator *modificator)
{
    int i = 0;
    int idx = -1;

    for(const auto &mod : modificators)
    {
        if(mod == modificator)
        {
            idx = i;
            break;
        }
        ++i;
    }

    return idx;
}

void SimulationSubject::swapModificators(Modificator *first, Modificator *second)
{
    auto iter = modificators.begin();
    decltype(iter) first_iter;
    decltype(iter) second_iter;

    if(first == second)
        return;

    for(UNUSED(iter); iter != modificators.end(); ++iter)
    {
        if(*iter == first)
            first_iter = iter;
        else if(*iter == second)
            second_iter = iter;
    }

    std::swap(first_iter, second_iter);
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

void SimulationSubject::collide(SimulationSubject *other)
{
    for(const auto &modificator: modificators)
    {
        modificator->collide(this, other);
    }
}

bool SimulationSubject::isCollision(const SimulationSubject *other)
{
    return radius + other->radius >= (position - other->position).abs();
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

    if(!data->atEnd())
    {
        int size = data->read();
        for(int i = 0; i < size; ++i)
            addModificator(restoreModificator(data));
    }

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
    char *name = new char[size+1];

    savable->read(RawBytes(name), size);
    name[size] = '\0';

    modificator = factory->get(name);

    delete[] name;
    return modificator;
}

Vector<RealNumber> SimulationSubject::restoreVector(SavableData *savable) const
{
    Vector<RealNumber> result(savable->read());

    for(int i = 0; i < result.size(); ++i)
        savable->read(RawBytes(&(result[i])), sizeof(RealNumber));

    return result;
}



