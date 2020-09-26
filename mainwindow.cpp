#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QTimer>

#include "physical/PhysicalObject.h"
#include "gui/simulationgraphicobject.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));

    PhysicalObject *phys = new PhysicalObject(1e14);
    phys->setPosition(Vector<>({10, 20}));
    phys->setVelocity(Vector<>({2, 2}));

    PhysicalObject *phys2 = new PhysicalObject(1e14);
    phys2->setPosition(Vector<>({100, 100}));
    phys2->setVelocity(Vector<>({-10, 4}));

    SimulationGraphicObject *obj = new SimulationGraphicObject(phys, this);
    SimulationGraphicObject *obj2 = new SimulationGraphicObject(phys2, this);
    ui->simulation->addGraphicObject(obj);
    ui->simulation->addGraphicObject(obj2);
    ui->simulation->addToSimulation(phys);
    ui->simulation->addToSimulation(phys2);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    ui->simulation->applyTime(0.02);
}

