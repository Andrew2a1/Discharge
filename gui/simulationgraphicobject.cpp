#include "simulationgraphicobject.h"
#include "attributeeditorwidget.h"
#include "physical/SimulationSubject.h"

#include <QPainter>

SimulationGraphicObject::SimulationGraphicObject(const SimulationGraphicObject &other):
    physical(other.physical)
{

}

SimulationGraphicObject::SimulationGraphicObject(SimulationSubjectPtr physical) :
    physical(physical)
{

}

SimulationSubjectPtr SimulationGraphicObject::getPhysical() const
{
    return physical;
}

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
    int radius = (int)getPhysical()->getRadius();
    return QRect(centre.x() - radius, centre.y() - radius, 2*radius, 2*radius);
}

void SimulationGraphicObject::draw(QPainter *painter)
{
    const QPoint centre = pos();
    QString charge = "M";

    if(getPhysical()->getElectricCharge() > 0)
        charge = "+";
    else if(getPhysical()->getElectricCharge() < 0)
        charge = "-";

    painter->drawEllipse(centre,
                         (int)getPhysical()->getRadius(),
                         (int)getPhysical()->getRadius());

    painter->drawText(getBounds(), Qt::AlignCenter , charge);
}

AttributeEditorWidget *SimulationGraphicObject::createAttributeEditor(QWidget *parent)
{
    AttributeEditorWidget* attrEdit = GraphicObject::createAttributeEditor(parent);

    attrEdit->addDoubleAttr("Radius",
                            [=](double radius) {
                                getPhysical()->setRadius(radius);
                            },
                            getPhysical()->getRadius());

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

    attrEdit->addSection("Electrostatic");

    attrEdit->addDoubleAttr("Charge",
                            [=](double charge) {
                                getPhysical()->setElectricCharge(charge);
                            },
                            getPhysical()->getElectricCharge());

    return attrEdit;
}

GraphicObject *SimulationGraphicObject::clone() const
{
    SimulationSubjectPtr subject(new SimulationSubject(*physical));
    return new SimulationGraphicObject(subject);
}

