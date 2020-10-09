#ifndef DRAGGABLEGRAPHIC_H
#define DRAGGABLEGRAPHIC_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class GraphicObject;

class DraggableGraphic : public QWidget
{
    Q_OBJECT

private:
    GraphicObject *graphic;
    QLabel *preview;
    QPixmap pixmap;

public:
    explicit DraggableGraphic(GraphicObject *graphic,
                              QWidget *parent = nullptr);

    ~DraggableGraphic();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QByteArray getDraggableData();

    void createPixmap();
    void createLayout();
};

#endif // DRAGGABLEGRAPHIC_H
