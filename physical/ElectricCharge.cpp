#include "ElectricCharge.h"
#include "ChargeModifier.h"
#include "ChargeState.h"
#include "PhysicalMemento.h"

ElectricCharge::ElectricCharge(double charge, double mass) :
    PhysicalObject(mass),
    charge(charge)
{
    setModifier(new ChargeModifier);
}

double ElectricCharge::getCharge() const
{
    return charge;
}

void ElectricCharge::setCharge(double charge)
{
    this->charge = charge;
}

PhysicalMemento *ElectricCharge::createMemento() const
{
    PhysicalMemento *memento = new PhysicalMemento();
    ChargeState *current = new ChargeState;

    current->mass = getMass();
    current->position = getPosition();
    current->velocity = getVelocity();
    current->charge = getCharge();

    memento->setState(current);
    return memento;
}

void ElectricCharge::restoreMemento(const PhysicalMemento *memento)
{
    ChargeState* charge_state = dynamic_cast<ChargeState*>(memento->getState());

    if(charge_state)
        setCharge(charge_state->charge);

    PhysicalObject::restoreMemento(memento);
}
