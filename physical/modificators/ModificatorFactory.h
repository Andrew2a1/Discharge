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
    static void deleteInstance();

    Modificator *get(const std::string &name);
    std::list<std::string> names() const;

    bool hasItem(const std::string &name) const;

protected:
    ModificatorFactory();
};

#endif // MODIFICATORFACTORY_H
