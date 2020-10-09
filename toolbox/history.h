#ifndef HISTORY_H
#define HISTORY_H

#include <list>

template<typename T>
class History
{
private:
    std::list<T> history;
    int currentIndex = -1;
    unsigned maxSize = 64;

public:
    int getMaxSize() const {
        return maxSize;
    }

    void setMaxSize(unsigned newMaxSize){
        maxSize = newMaxSize;

        while(history.size() > maxSize)
            removeFirst();
    }

    bool hasNext() const {
        return currentIndex < static_cast<int>(history.size()) - 1;
    }

    bool hasPrevious() const {
        return currentIndex > 0;
    }

    bool isEmpty() const {
        return history.empty();
    }

    void add(const T& el) {
        while(hasNext())
            history.pop_back();

        if(history.size() > maxSize)
            removeFirst();

        currentIndex += 1;
        history.push_back(el);
    }

    const T& previous() {
        currentIndex -= 1;
        return at(currentIndex);
    }

    const T& next() {
        currentIndex += 1;
        return at(currentIndex);
    }

    const T& current() const {
        return at(currentIndex);
    }

private:
    void removeFirst() {
        history.pop_front();
        currentIndex -= 1;
    }

    const T& at(int idx) const {
        int i = 0;
        for(auto &item : history)
            if(i++ == idx)
                return item;
        return history.front();
    }
};

#endif // HISTORY_H
