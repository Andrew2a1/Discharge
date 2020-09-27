#include "simulationgraphicobject.h"
#include "physical/PhysicalObject.h"
#include <QPainter>

SimulationGraphicObject::SimulationGraphicObject(PhysicalObject *physicalObject,
                                                 QObject *parent) :
    GraphicObject(parent),
    physical(physicalObject)
{

}

SimulationGraphicObject::~SimulationGraphicObject()
{
    delete physical;
}

void SimulationGraphicObject::setPosition(const QPoint &newPosition)
{
    Vector<double> position(2);
    position[0] = newPosition.x();
    position[1] = newPosition.y();

    physical->setPosition(position);
}

QPoint SimulationGraphicObject::pos() const
{
    const Vector<double> &position = physical->getPosition();
    return QPoint(position[0], position[1]);
}

QRect SimulationGraphicObject::getBounds() const
{
    const QPoint centre = pos();
    return QRect(centre.x() - RADIUS, centre.y() - RADIUS, 2*RADIUS, 2*RADIUS);
}

void SimulationGraphicObject::draw(QPainter *painter)
{
    const QPoint centre = pos();
    painter->drawEllipse(centre, RADIUS, RADIUS);
}

GraphicObject *SimulationGraphicObject::clone() const
{
    PhysicalObject *cpy = new PhysicalObject(*physical);
    return new SimulationGraphicObject(cpy, parent());
}
