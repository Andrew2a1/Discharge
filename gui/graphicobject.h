#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <QObject>

class QPainter;

class GraphicObject : public QObject
{
    Q_OBJECT  

public:
    explicit GraphicObject(QObject *parent = nullptr);

    virtual void setPosition(const QPoint &newPosition);
    virtual QPoint pos() const;

    virtual QRect getBounds() const;
    virtual void draw(QPainter *painter);

    virtual GraphicObject* clone() const;

    bool covers(const QPoint &point);
};

#endif // GRAPHICOBJECT_H
