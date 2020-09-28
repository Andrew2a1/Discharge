#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QTimer>

#include "physical/PhysicalObject.h"
#include "gui/simulationgraphicobject.h"
#include "gui/draggablegraphic.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));

    createGraphicObjects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGraphicObjects()
{
    PhysicalObject *phys = new PhysicalObject(1e14);
    phys->setPosition(Vector<>({0, 0}));
    phys->setVelocity(Vector<>({0, 0}));

    SimulationGraphicObject *obj = new SimulationGraphicObject(phys, this);
    DraggableGraphic *drag = new DraggableGraphic(obj, this);
    ui->palette->addWidget(drag);
}
