#ifndef HISTORY_H
#define HISTORY_H

#include <QList>

template<typename T>
class History
{
private:
    QList<T> history;
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
        return currentIndex < history.size() - 1;
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
        return history[currentIndex];
    }

    const T& next() {
        currentIndex += 1;
        return history[currentIndex];
    }

    const T& current() const {
        return history[currentIndex];
    }

private:
    void removeFirst() {
        history.pop_front();
        currentIndex = history.size() ? std::max(currentIndex - 1, 0) : -1;
    }
};

#endif // HISTORY_H
