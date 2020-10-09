#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "physical/PhysicalObjectPtr.h"
#include "gui/simulationwidget.h"
#include "gui/copymanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    CopyManager *copyManager;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    SimulationWidget *getActiveSim() const;

    void configureTabWidget();

    void createGraphicObjects();
    void createPhysical();
    void createElectrostatic();

    void setTo2D(const PhysicalObjectPtr &physical);

private slots:
    void addSimulationTab();
    void removeTab(int idx);

    void showAbout() const;
};
#endif // MAINWINDOW_H
