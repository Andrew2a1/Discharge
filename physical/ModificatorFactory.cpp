#include "ModificatorFactory.h"
#include "Modificator.h"

#include "ClassicModificator.h"

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
}

Modificator *ModificatorFactory::get(const std::string &name)
{
    for(const auto &modificator: modificators)
        if(modificator->name() == name)
            return modificator;

    return nullptr;
}
