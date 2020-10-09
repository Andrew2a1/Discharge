#ifndef PHYSICALGRAPHICOBJECT_H
#define PHYSICALGRAPHICOBJECT_H

#include "simulationgraphicobject.h"
#include "physical/PhysicalObjectPtr.h"

class PhysicalGraphicObject : public SimulationGraphicObject
{
private:
    PhysicalObjectPtr physical;

public:
    PhysicalGraphicObject(PhysicalObjectPtr physicalObject);

    virtual PhysicalObjectPtr getPhysical() const override;
    virtual GraphicObject *clone() const override;
};

#endif // PHYSICALGRAPHICOBJECT_H
