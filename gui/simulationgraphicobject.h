#ifndef SIMULATIONGRAPHICOBJECT_H
#define SIMULATIONGRAPHICOBJECT_H

#include "graphicobject.h"
#include "physical/PhysicalObjectPtr.h"

constexpr int RADIUS = 20;

class SimulationGraphicObject : public GraphicObject
{
public:
    virtual ~SimulationGraphicObject() = default;
    virtual PhysicalObjectPtr getPhysical() const = 0;

    void setPosition(const QPoint &newPosition) override;
    QPoint pos() const override;

    virtual QRect getBounds() const override;
    virtual void draw(QPainter *painter) override;
};

#endif // SIMULATIONGRAPHICOBJECT_H
