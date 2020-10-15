#ifndef MOVABLEMODIFICATOR_H
#define MOVABLEMODIFICATOR_H

#include "Modificator.h"

class MovableModificator : public Modificator
{
public:
    virtual std::string name() const override;
    virtual void applyTime(SimulationSubject *subject, RealNumber dt) const override;

};

#endif // MOVABLEMODIFICATOR_H
