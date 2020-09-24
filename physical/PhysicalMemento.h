#ifndef PHYSICALMEMENTO_H
#define PHYSICALMEMENTO_H

class PhysicalObject;
class ElectricCharge;
class PhysicalState;

class PhysicalMemento
{
    friend class PhysicalObject;
    friend class ElectricCharge;

private:
    PhysicalState *state = nullptr;

    void setState(PhysicalState *state);
    PhysicalState *getState() const;

protected:
    PhysicalMemento() = default;

public:
    virtual ~PhysicalMemento();
};

#endif // PHYSICALMEMENTO_H
