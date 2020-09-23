#ifndef PHYSICALMEMENTO_H
#define PHYSICALMEMENTO_H

class PhysicalObject;
class PhysicalState;

class PhysicalMemento
{
    friend class PhysicalObject;

private:
    PhysicalState *state = nullptr;

    void setState(PhysicalState *state);
    PhysicalState *getState() const;

public:
    ~PhysicalMemento();
};

#endif // PHYSICALMEMENTO_H
