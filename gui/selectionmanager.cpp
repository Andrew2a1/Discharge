#include "selectionmanager.h"

SelectionManager::SelectionManager(const QList<GraphicObjectPtr> &graphicObjects,
                                   QObject *parent) :
    QObject(parent),
    graphicObjects(graphicObjects)
{

}

const QList<GraphicObjectPtr> &SelectionManager::getSelected() const
{
    return selected;
}

void SelectionManager::add(const GraphicObjectPtr &graphic)
{
    if(!selected.contains(graphic))
        selected.append(graphic);
}

void SelectionManager::addFromRect(const QRect &newSeletion)
{
    for(const auto& graphic : graphicObjects)
        if(newSeletion.contains(graphic->getBounds()))
            add(graphic);
    selection = newSeletion;
}

bool SelectionManager::contains(const QPoint &point) const
{
    for(const auto& obj : selected)
        if(obj->getBounds().contains(point))
            return true;
    return false;
}

bool SelectionManager::contains(const GraphicObjectPtr &graphic) const
{
    return selected.contains(graphic);
}

bool SelectionManager::isEmpty() const
{
    return selected.isEmpty();
}

const QRect &SelectionManager::getRect() const
{
    return selection;
}

void SelectionManager::clear()
{
    selection = QRect();
    selected.clear();
}
