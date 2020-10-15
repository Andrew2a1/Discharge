#include "ModificatorFactory.h"
#include "Modificator.h"

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
    // TODO: FIll modificator list
}

Modificator *ModificatorFactory::get(const std::string &name)
{
    for(const auto &modificator: modificators)
        if(modificator->name() == name)
            return modificator;

    return nullptr;
}
