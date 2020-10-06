#ifndef COPYMANAGER_H
#define COPYMANAGER_H

#include <QObject>
#include <QList>

#include "graphicobject.h"

class CopyManager : public QObject
{
    Q_OBJECT

private:
    QList<GraphicObjectPtr> copied;

public:
    explicit CopyManager(QObject *parent = nullptr);

    void setCopied(const QList<GraphicObjectPtr> &copied);
    const QList<GraphicObjectPtr> &getCopied() const;

    bool isEmpty() const;
};

#endif // COPYMANAGER_H
