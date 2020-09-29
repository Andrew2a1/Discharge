#ifndef SAVABLE_DATA_H
#define SAVABLE_DATA_H

class SavableData
{
private:
    char *data;

public:
    SavableData(char* newData = nullptr);
    virtual ~SavableData();

    void set(char* newData);
    const char *get() const;
};


#endif // SAVABLE_DATA_H
