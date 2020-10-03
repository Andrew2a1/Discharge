#include "SavableData.h"

SavableData::SavableData(char* newData, unsigned length = 0) :
    data(newData),
    length(length)
{

}

SavableData::~SavableData()
{
    delete data;
}

void SavableData::set(char* newData, unsigned newLength)
{
    delete data;
    data = newData;
    length = newLength;
}

const char *SavableData::get() const
{
    return data;
}

unsigned SavableData::size() const
{
    return length;
}