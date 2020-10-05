#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <memory>

class QWidget;
class AttributeEditorWidget;

class QPoint;
class QRect;
class QPainter;

class GraphicObject
{
public:
    virtual ~GraphicObject() = default;

    virtual void setPosition(const QPoint &newPosition);
    virtual QPoint pos() const;

    virtual QRect getBounds() const;
    virtual void draw(QPainter *painter);

    virtual GraphicObject* clone() const;
    virtual AttributeEditorWidget *createAttributeEditor(QWidget *parent);

    bool covers(const QPoint &point);
};

typedef std::shared_ptr<GraphicObject> GraphicObjectPtr;

#endif // GRAPHICOBJECT_H
