#ifndef SIMULATIONGRAPHICOBJECT_H
#define SIMULATIONGRAPHICOBJECT_H

#include "graphicobject.h"
#include "physical/SimulationSubjectPtr.h"

constexpr int RADIUS = 20;

class SimulationGraphicObject : public GraphicObject
{
private:
    SimulationSubjectPtr physical;

public:
    SimulationGraphicObject(const SimulationGraphicObject &other);
    SimulationGraphicObject(SimulationSubjectPtr physical);
    virtual ~SimulationGraphicObject() = default;
    virtual SimulationSubjectPtr getPhysical() const;

    void setPosition(const QPoint &newPosition) override;
    QPoint pos() const override;

    virtual QRect getBounds() const override;
    virtual void draw(QPainter *painter) override;

    virtual AttributeEditorWidget *createAttributeEditor(QWidget *parent) override;
    virtual GraphicObject* clone() const override;
};

#endif // SIMULATIONGRAPHICOBJECT_H
