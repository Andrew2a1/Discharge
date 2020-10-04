#include "graphicobject.h"
#include <QRect>

void GraphicObject::setPosition(const QPoint &newPosition)
{
    Q_UNUSED(newPosition);
}

QPoint GraphicObject::pos() const
{
    return QPoint();
}

QRect GraphicObject::getBounds() const
{
    return QRect();
}

void GraphicObject::draw(QPainter *painter)
{
    Q_UNUSED(painter);
}

GraphicObject *GraphicObject::clone() const
{
    GraphicObject *cpy = new GraphicObject;
    cpy->setPosition(this->pos());
    return cpy;
}

bool GraphicObject::covers(const QPoint &point)
{
    return getBounds().contains(point);
}
