#include "SavableData.h"

SavableData::SavableData(char* newData) :
    data(newData)
{

}

SavableData::~SavableData()
{
    delete data;
}

void SavableData::set(char *newData)
{
    delete data;
    data = newData;
}

const char *SavableData::get() const
{
    return data;
}