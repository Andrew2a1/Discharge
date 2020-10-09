#include "zoomwidget.h"
#include "ui_zoomwidget.h"

ZoomWidget::ZoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomWidget)
{
    ui->setupUi(this);

    connect(ui->fitButton, SIGNAL(pressed()), this, SIGNAL(fitRequested()));
    connect(ui->zoomInButton, SIGNAL(pressed()), this, SLOT(zoomIn()));
    connect(ui->zoomOutButton, SIGNAL(pressed()), this, SLOT(zoomOut()));

    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setZoom(int)));
    connect(ui->zoomSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setZoom(int)));

    connect(this, SIGNAL(zoomUpdated(int)), ui->zoomSlider, SLOT(setValue(int)));
    connect(this, SIGNAL(zoomUpdated(int)), ui->zoomSpinBox, SLOT(setValue(int)));
}

ZoomWidget::~ZoomWidget()
{
    delete ui;
}

int ZoomWidget::getZoom() const
{
    return zoom;
}

void ZoomWidget::setZoom(int newZoom)
{
    zoom = newZoom;
    emit zoomUpdated(zoom);
}

void ZoomWidget::zoomIn()
{
    zoom += 10;
    emit zoomUpdated(zoom);
}

void ZoomWidget::zoomOut()
{
    zoom -= 10;
    emit zoomUpdated(zoom);
}
