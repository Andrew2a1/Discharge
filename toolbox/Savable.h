#ifndef SAVABLE_H
#define SAVABLE_H

class SavableData;

class Savable
{
public:
    SavableData* save() const;
    void restore(const SavableData *data);

protected:
    virtual char* toBytes() const = 0;
    virtual void fromBytes(const char* bytes) = 0;
};

#endif // SAVABLE_H