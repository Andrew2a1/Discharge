#include "graphicobject.h"
#include "attributeeditorwidget.h"

#include <QRect>
#include <QPoint>
#include <QtDebug>

void GraphicObject::setPosition(const QPoint &newPosition)
{
    Q_UNUSED(newPosition)
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
    Q_UNUSED(painter)
}

GraphicObject *GraphicObject::clone() const
{
    GraphicObject *cpy = new GraphicObject;
    cpy->setPosition(this->pos());
    return cpy;
}

AttributeEditorWidget *GraphicObject::createAttributeEditor(QWidget *parent)
{
    return new AttributeEditorWidget(this, parent);
}

bool GraphicObject::covers(const QPoint &point)
{
    return getBounds().contains(point);
}
