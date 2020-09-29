#include "Savable.h"
#include "SavableData.h"

SavableData *Savable::save() const
{
    SavableData *savable = new SavableData(toBytes());
    return savable;
}

void Savable::restore(const SavableData *data)
{
    fromBytes(data->get());
}