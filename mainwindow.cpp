#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QTimer>

#include "physical/PhysicalObject.h"
#include "physical/ElectricCharge.h"

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
    QGridLayout *physicals = new QGridLayout(ui->physicalBox);

    PhysicalObject *phys = new PhysicalObject(1e14);
    phys->setPosition(Vector<>({0, 0}));
    phys->setVelocity(Vector<>({0, 0}));

    SimulationGraphicObject *obj = new SimulationGraphicObject(phys, this);

    physicals->addWidget(new DraggableGraphic(obj, this));

    QGridLayout *electrostatic = new QGridLayout(ui->electrostaticBox);

    ElectricCharge *electric = new ElectricCharge(1.0, 1);
    electric->setPosition(Vector<>({0, 0}));
    electric->setVelocity(Vector<>({0, 0}));

    SimulationGraphicObject *obj2 = new SimulationGraphicObject(electric, this);

    electrostatic->addWidget(new DraggableGraphic(obj2, this));
}
