#include "SavableData.h"

SavableData::SavableData(unsigned reserveSize)
{
    this->reserve(reserveSize);
}

void SavableData::reserve(unsigned length)
{
    data.reserve(length);
}

void SavableData::add(const char *newData, unsigned size)
{
    for(unsigned i = 0; i < size; ++i)
        data.push_back(newData[i]);
}

void SavableData::add(char byte)
{
    data.push_back(byte);
}

void SavableData::add(const SavableData &other)
{
    this->reserve(this->size() + other.size());
    this->add(other.getRaw(), other.size());
}

const char *SavableData::getRaw(unsigned start) const
{
    return data.data() + start;
}

unsigned SavableData::size() const
{
    return data.size();
}

void SavableData::clear()
{
    data.clear();
}
