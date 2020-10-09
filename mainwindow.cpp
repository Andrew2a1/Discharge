#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTabBar>
#include <QPushButton>

#include <QAction>
#include <QTimer>

#include "physical/PhysicalObject.h"
#include "physical/ElectricCharge.h"
#include "physical/PhysicalObjectPtr.h"

#include "gui/physicalgraphicobject.h"
#include "gui/electrostaticgraphicobject.h"
#include "gui/draggablegraphic.h"


#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    copyManager = new CopyManager(this);
    ui->simulation->setCopyManager(copyManager);

    configureTabWidget();

    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    createGraphicObjects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureTabWidget()
{
    QPushButton *newSimButton = new QPushButton("+", ui->tabWidget);
    ui->tabWidget->setCornerWidget(newSimButton);

    QTabBar *tabBar = ui->tabWidget->tabBar();
    tabBar->tabButton(0, QTabBar::RightSide)->hide();

    connect(newSimButton, &QPushButton::clicked, this, &MainWindow::addSimulationTab);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::removeTab);
}

void MainWindow::addSimulationTab()
{
    const QString desc = QString("Sim%1").arg(ui->tabWidget->count() + 1);
    SimulationWidget *simWidget = new SimulationWidget(ui->tabWidget);

    simWidget->setCopyManager(copyManager);
    ui->tabWidget->addTab(simWidget, desc);

    QTabBar *tabBar = ui->tabWidget->tabBar();
    tabBar->tabButton(0, QTabBar::RightSide)->show();
}

void MainWindow::removeTab(int idx)
{
    if(ui->tabWidget->count() == 2)
    {
        QTabBar *tabBar = ui->tabWidget->tabBar();
        tabBar->tabButton(1 - idx, QTabBar::RightSide)->hide();
    }
    if(ui->tabWidget->count() > 1)
        ui->tabWidget->removeTab(idx);
}

void MainWindow::createGraphicObjects()
{
    createPhysical();
    createElectrostatic();
}

void MainWindow::createPhysical()
{
    QGridLayout *physicals = new QGridLayout(ui->physicalBox);

    PhysicalObjectPtr phys(new PhysicalObject(1e12));
    setTo2D(phys);

    PhysicalGraphicObject *physicalGraphic = new PhysicalGraphicObject(phys);
    physicals->addWidget(new DraggableGraphic(physicalGraphic, this));
}

void MainWindow::createElectrostatic()
{
    QGridLayout *electrostatic = new QGridLayout(ui->electrostaticBox);
    electrostatic->setAlignment(Qt::AlignTop);

    ElectricChargePtr electricNeutral(new ElectricCharge(1.0, 0));
    ElectricChargePtr electricPlus(new ElectricCharge(1.0, 1e-4));
    ElectricChargePtr electricMinus(new ElectricCharge(1.0, -1e-4));

    setTo2D(electricNeutral);
    setTo2D(electricPlus);
    setTo2D(electricMinus);

    ElectrostaticGraphicObject *neutral = new ElectrostaticGraphicObject(electricNeutral);
    ElectrostaticGraphicObject *plus = new ElectrostaticGraphicObject(electricPlus);
    ElectrostaticGraphicObject *minus = new ElectrostaticGraphicObject(electricMinus);

    electrostatic->addWidget(new DraggableGraphic(neutral, this), 0, 0);
    electrostatic->addWidget(new DraggableGraphic(plus, this), 0, 1);
    electrostatic->addWidget(new DraggableGraphic(minus, this), 1, 0, Qt::AlignTop);
}

void MainWindow::setTo2D(const PhysicalObjectPtr &physical)
{
    physical->setPosition(Vector<>({0, 0}));
    physical->setVelocity(Vector<>({0, 0}));
}

