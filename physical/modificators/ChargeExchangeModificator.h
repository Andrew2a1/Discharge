#ifndef CHARGEEXCHANGEMODIFICATOR_H
#define CHARGEEXCHANGEMODIFICATOR_H

#include "Modificator.h"

class ChargeExchangeModificator : public Modificator
{
public:
    virtual std::string name() const override;
    virtual void collide(SimulationSubject *subject, SimulationSubject *other) override;
};

#endif // CHARGEEXCHANGEMODIFICATOR_H
