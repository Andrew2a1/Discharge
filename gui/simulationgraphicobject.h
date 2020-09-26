#ifndef SIMULATIONGRAPHICOBJECT_H
#define SIMULATIONGRAPHICOBJECT_H

#include "graphicobject.h"

class PhysicalObject;

constexpr int RADIUS = 20;

class SimulationGraphicObject : public GraphicObject
{
    Q_OBJECT

private:
    PhysicalObject *physical;

public:
    explicit SimulationGraphicObject(PhysicalObject *physicalObject,
                                     QObject *parent = nullptr);

    void setPosition(const QPoint &newPosition) override;
    QPoint pos() const override;

    virtual QRect getBounds() const override;
    virtual void draw(QPainter *painter) override;

    virtual GraphicObject* clone() const override;
};

#endif // SIMULATIONGRAPHICOBJECT_H
