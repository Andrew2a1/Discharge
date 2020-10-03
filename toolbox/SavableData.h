#ifndef SAVABLE_DATA_H
#define SAVABLE_DATA_H

#include <vector>

#define PackObject(obj) (const char*)((&obj)), (sizeof((obj)))
#define PackObjectPtr(obj) (const char*)((obj)), (sizeof(*(obj)))

class SavableData
{
private:
    std::vector<char> data;

public:
    SavableData(unsigned reserveSize = 0);
    void reserve(unsigned length);

    void add(const char *newData, unsigned size);
    const char *getRaw(unsigned start = 0) const;
    
    unsigned size() const;
    void clear();
};


#endif // SAVABLE_DATA_H
