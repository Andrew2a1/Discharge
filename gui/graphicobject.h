#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

class QPoint;
class QRect;

#include <memory>

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

    bool covers(const QPoint &point);
};

typedef std::shared_ptr<GraphicObject> GraphicObjectPtr;

#endif // GRAPHICOBJECT_H
