#ifndef PROTOTYPEMANAGER_H
#define PROTOTYPEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>

#include "graphicobject.h"

class PrototypeManager : public QObject
{
    Q_OBJECT

private:
    QMap<QString, GraphicObjectPtr> prototypes;

public:
    explicit PrototypeManager(QObject *parent = nullptr);

    GraphicObjectPtr get(const QString &name) const;
    QList<GraphicObjectPtr> values() const;
    QList<QString> names() const;

    void add(const QString &name, const GraphicObjectPtr &object);

    bool isValid(const QString &name) const;
};

#endif // PROTOTYPEMANAGER_H
