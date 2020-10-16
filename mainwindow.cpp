#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include <QTabBar>
#include <QPushButton>

#include <QAction>
#include <QGridLayout>

#include "physical/SimulationSubject.h"
#include "physical/SimulationSubjectPtr.h"

#include "toolbox/Savable.h"
#include "toolbox/SavableData.h"

#include "physical/modificators/ModificatorFactory.h"

#include "gui/simulationgraphicobject.h"
#include "gui/draggablegraphic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    copyManager = new CopyManager(this);
    ui->simulation->setCopyManager(copyManager);

    prototypeManager = new PrototypeManager(this);
    ui->simulation->setPrototypeManager(prototypeManager);
    createGraphicObjects();

    configureTabWidget();

    connect(ui->action_New, &QAction::triggered, this, &MainWindow::addSimulationTab);
    connect(ui->action_Exit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->action_Redo, &QAction::triggered, this, &MainWindow::redo);
    connect(ui->action_Undo, &QAction::triggered, this, &MainWindow::undo);

    connect(ui->action_Copy, &QAction::triggered, this, &MainWindow::copy);
    connect(ui->action_Cut, &QAction::triggered, this, &MainWindow::cut);
    connect(ui->action_Paste, &QAction::triggered, this, &MainWindow::paste);
    connect(ui->actionAbout_Discharge, &QAction::triggered, this, &MainWindow::showAbout);

    connect(ui->actionSave, &QAction::triggered, [=](){askSaveToFile(true);});
    connect(ui->actionSave_as, &QAction::triggered, [=](){askSaveToFile(false);});
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::askOpenFiles);

    connect(ui->menu_Edit, &QMenu::aboutToShow, this, &MainWindow::updateActionsEnabled);
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

SimulationWidget *MainWindow::addSimulationTab()
{
    const QString desc = QString("Sim%1").arg(ui->tabWidget->count() + 1);
    SimulationWidget *simWidget = new SimulationWidget(ui->tabWidget);

    simWidget->setCopyManager(copyManager);
    simWidget->setPrototypeManager(prototypeManager);
    ui->tabWidget->addTab(simWidget, desc);

    QTabBar *tabBar = ui->tabWidget->tabBar();
    tabBar->tabButton(0, QTabBar::RightSide)->show();

    return simWidget;
}

void MainWindow::removeTab(int idx)
{
    if(ui->tabWidget->count() == 2)
    {
        QTabBar *tabBar = ui->tabWidget->tabBar();
        tabBar->tabButton(1 - idx, QTabBar::RightSide)->hide();
    }
    if(ui->tabWidget->count() > 1) {
        QWidget *widget = ui->tabWidget->widget(idx);
        ui->tabWidget->removeTab(idx);
        widget->deleteLater();
    }
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

    SimulationSubjectPtr phys(new SimulationSubject(2, 20, 1e12));
    addBasicModificators(phys);
    phys->addModificator("GravityForce");

    GraphicObjectPtr physicalGraphic(new SimulationGraphicObject(phys));

    physicals->addWidget(new DraggableGraphic(physicalGraphic, this));
    prototypeManager->add("Mass", physicalGraphic);
}

void MainWindow::createElectrostatic()
{
    QGridLayout *electrostatic = new QGridLayout(ui->electrostaticBox);
    electrostatic->setAlignment(Qt::AlignTop);

    SimulationSubjectPtr electricNeutral(new SimulationSubject(2, 15, 1.0));
    SimulationSubjectPtr electricPlus(new SimulationSubject(2, 15, 1.0, 1e-4));
    SimulationSubjectPtr electricMinus(new SimulationSubject(2, 15, 1.0, -1e-4));

    addBasicModificators(electricNeutral);
    addBasicModificators(electricPlus);
    addBasicModificators(electricMinus);

    electricNeutral->addModificator("ElectrostaticForce");
    electricPlus->addModificator("ElectrostaticForce");
    electricMinus->addModificator("ElectrostaticForce");

    GraphicObjectPtr neutral(new SimulationGraphicObject(electricNeutral));
    GraphicObjectPtr plus(new SimulationGraphicObject(electricPlus));
    GraphicObjectPtr minus(new SimulationGraphicObject(electricMinus));

    electrostatic->addWidget(new DraggableGraphic(neutral, this), 0, 0);
    electrostatic->addWidget(new DraggableGraphic(plus, this), 0, 1);
    electrostatic->addWidget(new DraggableGraphic(minus, this), 1, 0, Qt::AlignTop);

    prototypeManager->add("Neutral", neutral);
    prototypeManager->add("Plus", plus);
    prototypeManager->add("Minus", minus);
}

void MainWindow::addBasicModificators(SimulationSubjectPtr subject)
{
    static const std::vector<std::string> basic = {"Movable", "ForceSensitive",
                                                   "PhysicalCollision", "ChargeExchange"};

    for(const auto &name: basic)
    {
        subject->addModificator(name);
    }
}

bool MainWindow::openFile(QString filename)
{
    QFile simFile(filename);
    SavableData savable;

    simFile.open(QIODevice::ReadOnly);

    if(!(simFile.read(4) == QString("DSIM").toLocal8Bit()))
        return false;

    QByteArray data = simFile.readAll();

    savable.reserve(data.size());
    savable.add(RawBytesConst(data.data()), data.size());

    SimulationWidget *added = addSimulationTab();
    added->restore(&savable);

    simFile.close();
    return true;
}

bool MainWindow::saveToFile(QString filename)
{
    SavableData *savable = getActiveSim()->save();

    QFile simFile(filename);
    simFile.open(QIODevice::WriteOnly);

    if(!simFile.isWritable())
        return false;

    simFile.write("DSIM", 4);
    simFile.write((const char*)(savable->getRaw()), savable->size());
    simFile.close();

    delete savable;
    return true;
}

void MainWindow::redo()
{
    SimulationWidget *active = getActiveSim();
    active->redo();
}

void MainWindow::undo()
{
    SimulationWidget *active = getActiveSim();
    active->undo();
}

void MainWindow::copy()
{
    SimulationWidget *active = getActiveSim();
    active->handleCopy();
}

void MainWindow::cut()
{
    SimulationWidget *active = getActiveSim();
    active->handleCut();
}

void MainWindow::paste()
{
    SimulationWidget *active = getActiveSim();
    active->handlePaste();
}

void MainWindow::askSaveToFile(bool override)
{
    QString name;

    if(lastSaved.isEmpty() || !override) {
        name = QFileDialog::getSaveFileName(this, tr("Open simulation file"),
                                            ".", tr("Discharge simulation (*.dsim)"));
    }
    else {
        name = lastSaved;
    }

    if(!name.isEmpty())
    {
        saveToFile(name);
        lastSaved = name;
    }
}

void MainWindow::askOpenFiles()
{
    QStringList filenames;
    filenames = QFileDialog::getOpenFileNames(this, tr("Open simulation file"),
                                                ".", tr("Discharge simulation (*.dsim)"));

    for(const auto &name: filenames)
    {
        openFile(name);
    }
}

