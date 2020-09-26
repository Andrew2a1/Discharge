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

    PhysicalObject *phys = new PhysicalObject(1);
    phys->setPosition(Vector<>({10, 10}));
    phys->setVelocity(Vector<>({20, 10}));

    SimulationGraphicObject *obj = new SimulationGraphicObject(phys, this);
    ui->simulation->addGraphicObject(obj);
    ui->simulation->addToSimulation(phys);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    ui->simulation->applyTime(0.02);
}

