#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <QTabBar>
#include <QPushButton>

#include <QAction>
#include <QTimer>

#include <QGridLayout>

#include "physical/PhysicalObject.h"
#include "physical/ElectricCharge.h"
#include "physical/PhysicalObjectPtr.h"

#include "gui/physicalgraphicobject.h"
#include "gui/electrostaticgraphicobject.h"
#include "gui/draggablegraphic.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    copyManager = new CopyManager(this);
    ui->simulation->setCopyManager(copyManager);

    configureTabWidget();

    connect(ui->action_Exit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->action_Redo, &QAction::triggered, ui->simulation, &SimulationWidget::redo);
    connect(ui->action_Undo, &QAction::triggered, ui->simulation, &SimulationWidget::undo);

    connect(ui->action_Copy, &QAction::triggered, ui->simulation, &SimulationWidget::handleCopy);
    connect(ui->action_Cut, &QAction::triggered, ui->simulation, &SimulationWidget::handleCut);
    connect(ui->action_Paste, &QAction::triggered, ui->simulation, &SimulationWidget::handlePaste);
    connect(ui->actionAbout_Discharge, &QAction::triggered, this, &MainWindow::showAbout);

    connect(ui->menu_Edit, &QMenu::aboutToShow, this, &MainWindow::updateActionsEnabled);

    createGraphicObjects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

SimulationWidget *MainWindow::getActiveSim() const
{
    QWidget *current = ui->tabWidget->currentWidget();
    return qobject_cast<SimulationWidget*>(current);
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

void MainWindow::showAbout() const
{
    QMessageBox *about = new QMessageBox(QMessageBox::Information,
                                         tr("About"),
                                         tr("Discharge is simple Qt5 graphic application "
                                            "for basic electrostatic simulations.\n"
                                            "Project: https://github.com/Andrew2a1/Discharge"),
                                         QMessageBox::Ok,
                                         this->centralWidget());
    about->exec();
}

void MainWindow::updateActionsEnabled()
{
    SimulationWidget *active = getActiveSim();

    ui->action_Undo->setEnabled(active->hasHistoryPrevious());
    ui->action_Redo->setEnabled(active->hasHistoryNext());

    ui->action_Copy->setEnabled(active->hasSelected());
    ui->action_Cut->setEnabled(active->hasSelected());
    ui->action_Paste->setEnabled(active->hasPasteData());
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

