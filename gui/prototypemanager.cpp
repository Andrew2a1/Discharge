#include "prototypemanager.h"

PrototypeManager::PrototypeManager(QObject *parent) :
    QObject(parent)
{

}

GraphicObjectPtr PrototypeManager::get(const QString &name) const
{
    return prototypes[name];
}

QList<GraphicObjectPtr> PrototypeManager::values() const
{
    return prototypes.values();
}

QList<QString> PrototypeManager::names() const
{
    return prototypes.keys();
}

void PrototypeManager::add(const QString &name, const GraphicObjectPtr &object)
{
    prototypes[name] = object;
}

bool PrototypeManager::isValid(const QString &name) const
{
    return prototypes.contains(name);
}
