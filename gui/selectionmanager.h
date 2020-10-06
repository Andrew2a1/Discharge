#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QObject>
#include <QRect>
#include <QList>

#include "graphicobject.h"

class SelectionManager : public QObject
{
    Q_OBJECT

private:
    const QList<GraphicObjectPtr> &graphicObjects;
    QList<GraphicObjectPtr> selected;
    QRect selection;

public:
    explicit SelectionManager(const QList<GraphicObjectPtr> &graphicObjects,
                              QObject *parent = nullptr);

    const QList<GraphicObjectPtr> &getSelected() const;

    void addSelected(const GraphicObjectPtr &graphic);
    void addAllFrom(const QRect &newSeletion);

    bool contains(const QPoint &point) const;
    bool contains(const GraphicObjectPtr &graphic) const;
    bool isEmpty() const;

    const QRect &getSelection() const;
    void clearSelection();
};

#endif // SELECTIONMANAGER_H
