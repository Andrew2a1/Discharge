#ifndef MODIFICATORFACTORY_H
#define MODIFICATORFACTORY_H

#include <string>
#include <list>

#include "Modificator.h"

class ModificatorFactory
{
    static ModificatorFactory *unique;
    std::list<Modificator*> modificators;

public:
    ~ModificatorFactory();
    static ModificatorFactory *instance();

    Modificator *get(const std::string &name);

protected:
    ModificatorFactory();
};

#endif // MODIFICATORFACTORY_H
