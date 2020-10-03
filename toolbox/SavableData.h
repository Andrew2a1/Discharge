#ifndef SAVABLE_DATA_H
#define SAVABLE_DATA_H

class SavableData
{
private:
    char *data;
    unsigned length;

public:
    SavableData(char* newData = nullptr, unsigned length = 0);
    virtual ~SavableData();

    void set(char* newData, unsigned newLength);
    const char *get() const;

    unsigned size() const;
};


#endif // SAVABLE_DATA_H
