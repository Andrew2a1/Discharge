#ifndef SAVABLE_H
#define SAVABLE_H

class SavableData;

class Savable
{
public:
    virtual SavableData* save() const = 0;
    virtual void restore(const SavableData *data) = 0;
};

#endif // SAVABLE_H