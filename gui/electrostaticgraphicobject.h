#ifndef ELECTROSTATICGRAPHICOBJECT_H
#define ELECTROSTATICGRAPHICOBJECT_H

#include "simulationgraphicobject.h"
#include "physical/PhysicalObjectPtr.h"

class ElectrostaticGraphicObject : public SimulationGraphicObject
{
private:
    ElectricChargePtr electrostatic;

public:
    ElectrostaticGraphicObject(ElectricChargePtr electrostatic);

    virtual void draw(QPainter *painter) override;

    virtual PhysicalObjectPtr getPhysical() const override;
    virtual GraphicObject *clone() const override;

    virtual AttributeEditorWidget *createAttributeEditor(QWidget *parent) override;
};

#endif // ELECTROSTATICGRAPHICOBJECT_H
