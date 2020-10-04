#include "electrostaticgraphicobject.h"
#include "physical/ElectricCharge.h"
#include <QPainter>

ElectrostaticGraphicObject::ElectrostaticGraphicObject(ElectricChargePtr electrostatic) :
    electrostatic(electrostatic)
{

}

void ElectrostaticGraphicObject::draw(QPainter *painter)
{
    const QPoint centre = pos();
    QString charge = "N";

    if(electrostatic->getCharge() > 0)
        charge = "+";
    else if(electrostatic->getCharge() < 0)
        charge = "-";

    painter->drawEllipse(centre, RADIUS, RADIUS);
    painter->drawText(getBounds(), Qt::AlignCenter , charge);
}

PhysicalObjectPtr ElectrostaticGraphicObject::getPhysical() const
{
    return electrostatic;
}

GraphicObject *ElectrostaticGraphicObject::clone() const
{
    ElectricChargePtr clone(new ElectricCharge(*electrostatic));
    return new ElectrostaticGraphicObject(clone);
}
