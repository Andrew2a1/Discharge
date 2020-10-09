#include "copymanager.h"

CopyManager::CopyManager(QObject *parent) :
    QObject(parent)
{

}

void CopyManager::setCopied(const QList<GraphicObjectPtr> &copied)
{
    this->copied = copied;
}

const QList<GraphicObjectPtr> &CopyManager::getCopied() const
{
    return copied;
}

bool CopyManager::isEmpty() const
{
    return copied.isEmpty();
}
