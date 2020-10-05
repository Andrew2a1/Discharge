#include "simulationgraphicobject.h"
#include "attributeeditorwidget.h"
#include "physical/PhysicalObject.h"

#include <QPainter>

void SimulationGraphicObject::setPosition(const QPoint &newPosition)
{
    Vector<double> position(2);
    position[0] = newPosition.x();
    position[1] = newPosition.y();

    getPhysical()->setPosition(position);
}

QPoint SimulationGraphicObject::pos() const
{
    const Vector<double> &position = getPhysical()->getPosition();
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
    painter->drawText(getBounds(), Qt::AlignCenter ,"m");
}


AttributeEditorWidget *SimulationGraphicObject::createAttributeEditor(QWidget *parent)
{
    AttributeEditorWidget* attrEdit = GraphicObject::createAttributeEditor(parent);

    attrEdit->addDoubleAttr("Mass",
                            [=](double mass) {
                                getPhysical()->setMass(mass);
                            },
                            getPhysical()->getMass());

    attrEdit->addSection("Position");

    for(int i = 0; i < getPhysical()->getPosition().size(); ++i)
    {
        attrEdit->addDoubleAttr(QString("pos[%1]").arg(i),
                                [=](double pos) {
                                    Vector<double> vect(getPhysical()->getPosition());
                                    vect[i] = pos;
                                    getPhysical()->setPosition(vect);
                                    parent->updateGeometry();
                                },
                                getPhysical()->getPosition()[i]);
    }

    attrEdit->addSection("Velocity");

    for(int i = 0; i < getPhysical()->getVelocity().size(); ++i)
    {
        attrEdit->addDoubleAttr(QString("v[%1]").arg(i),
                                [=](double v) {
                                    Vector<double> vect(getPhysical()->getVelocity());
                                    vect[i] = v;
                                    getPhysical()->setVelocity(vect);
                                },
                                getPhysical()->getVelocity()[i]);
    }


    return attrEdit;
}

