#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <QWidget>

namespace Ui {
class ZoomWidget;
}

class ZoomWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::ZoomWidget *ui;
    int zoom = 100;

public:
    explicit ZoomWidget(QWidget *parent = nullptr);
    ~ZoomWidget();

    int getZoom() const;

public slots:
    void setZoom(int newZoom);

signals:
    void fitRequested();
    void zoomUpdated(int);

private slots:
    void zoomIn();
    void zoomOut();
};

#endif // ZOOMWIDGET_H
