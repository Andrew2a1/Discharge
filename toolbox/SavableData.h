#ifndef SAVABLE_DATA_H
#define SAVABLE_DATA_H

#include <vector>

#define PackObject(obj) (const char*)((&obj)), (sizeof((obj)))
#define PackObjectPtr(obj) (const char*)((obj)), (sizeof(*(obj)))

class SavableData
{
private:
    std::vector<char> data;
    unsigned cursor = 0;

public:
    SavableData(unsigned reserveSize = 0);
    void reserve(unsigned length);

    void add(char byte);
    void add(const char *newData, unsigned size);
    void add(const SavableData &other);

    const char *getRaw() const;
    unsigned read(char *destination, int maxAmount = -1);
    char read();

    unsigned pos() const;
    void seek(unsigned pos);
    bool atEnd() const;

    unsigned size() const;
    void clear();
};


#endif // SAVABLE_DATA_H
