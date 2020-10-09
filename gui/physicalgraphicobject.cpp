#include "physicalgraphicobject.h"
#include "physical/PhysicalObject.h"

PhysicalGraphicObject::PhysicalGraphicObject(PhysicalObjectPtr physicalObject) :
    physical(physicalObject)
{

}

PhysicalObjectPtr PhysicalGraphicObject::getPhysical() const
{
    return physical;
}

GraphicObject *PhysicalGraphicObject::clone() const
{
    PhysicalObjectPtr clone(new PhysicalObject(*physical));
    return new PhysicalGraphicObject(clone);
}

