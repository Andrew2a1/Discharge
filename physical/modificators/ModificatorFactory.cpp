#include "ModificatorFactory.h"
#include "Modificator.h"

#include "ClassicModificator.h"
#include "ChargeExchangeModificator.h"
#include "ElectrostaticForceModificator.h"
#include "ForceSensitiveModificator.h"
#include "GravityForceModificator.h"
#include "MovableModificator.h"
#include "PhysicalCollisionModificator.h"

ModificatorFactory *ModificatorFactory::unique = nullptr;

ModificatorFactory::~ModificatorFactory()
{
    for(auto &modificator: modificators)
        delete modificator;
}

ModificatorFactory *ModificatorFactory::instance()
{
    if(unique == nullptr)
        unique = new ModificatorFactory;

    return unique;
}

ModificatorFactory::ModificatorFactory()
{
    modificators.push_back(new ClassicModificator);
    modificators.push_back(new ChargeExchangeModificator);
    modificators.push_back(new ElectrostaticForceModificator);
    modificators.push_back(new ForceSensitiveModificator);
    modificators.push_back(new GravityForceModificator);
    modificators.push_back(new MovableModificator);
    modificators.push_back(new PhysicalCollisionModificator);
}

Modificator *ModificatorFactory::get(const std::string &name)
{
    for(const auto &modificator: modificators)
        if(modificator->name() == name)
            return modificator;

    return nullptr;
}

std::list<std::string> ModificatorFactory::names() const
{
    std::list<std::string> out;

    for(const auto &modificator: modificators)
        out.push_back(modificator->name());

    return out;
}

bool ModificatorFactory::hasItem(const std::string &name) const
{
    return std::find_if(modificators.begin(),
                        modificators.end(),
                        [&](Modificator *item){
                            return name == item->name();
                        }) != modificators.end();
}
