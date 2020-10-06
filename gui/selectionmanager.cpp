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

void SelectionManager::addSelected(const GraphicObjectPtr &graphic)
{
    if(!selected.contains(graphic))
        selected.append(graphic);
}

void SelectionManager::addAllFrom(const QRect &newSeletion)
{
    for(const auto& graphic : graphicObjects)
        if(selection.contains(graphic->getBounds()))
            addSelected(graphic);
    selection = newSeletion;
}

bool SelectionManager::contains(const GraphicObjectPtr &graphic) const
{
    return selected.contains(graphic);
}

bool SelectionManager::isEmpty() const
{
    return selected.isEmpty();
}

const QRect &SelectionManager::getSelection() const
{
    return selection;
}

void SelectionManager::clearSelection()
{
    selection = QRect();
    selected.clear();
}
