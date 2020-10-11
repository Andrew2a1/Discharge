#ifndef DRAGGABLEGRAPHIC_H
#define DRAGGABLEGRAPHIC_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

#include "graphicobject.h"

class DraggableGraphic : public QWidget
{
    Q_OBJECT

private:
    GraphicObjectPtr graphic;
    QLabel *preview;
    QPixmap pixmap;

public:
    explicit DraggableGraphic(GraphicObjectPtr graphic,
                              QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QByteArray getDraggableData();

    void createPixmap();
    void createLayout();
};

#endif // DRAGGABLEGRAPHIC_H
