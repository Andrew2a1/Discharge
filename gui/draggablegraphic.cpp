#include "draggablegraphic.h"
#include "graphicobject.h"

#include <QVBoxLayout>
#include <QPainter>

#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>

#include <QDebug>

DraggableGraphic::DraggableGraphic(GraphicObject *graphic, QWidget *parent) :
    QWidget(parent),
    graphic(graphic),
    pixmap(graphic->getBounds().adjusted(-4, -4, 4, 4).size())
{
    preview = new QLabel(this);

    createPixmap();
    preview->setPixmap(pixmap);

    createLayout();
}

void DraggableGraphic::createPixmap()
{
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(pixmap.rect().center() - graphic->pos());
    pixmap.fill(Qt::white);

    if(graphic)
        graphic->draw(&painter);

    painter.end();
}

void DraggableGraphic::mousePressEvent(QMouseEvent *event)
{
    if (!graphic)
        return;

    QByteArray itemData = getDraggableData();
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - pos());
    drag->start();
}

QByteArray DraggableGraphic::getDraggableData()
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream.writeRawData((char*)(&graphic), sizeof(graphic));

    return itemData;
}


void DraggableGraphic::createLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(preview, 0, Qt::AlignTop);
}


