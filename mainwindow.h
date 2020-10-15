#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "physical/SimulationSubjectPtr.h"
#include "gui/simulationwidget.h"
#include "gui/copymanager.h"
#include "gui/prototypemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QString lastSaved;

    CopyManager *copyManager;
    PrototypeManager *prototypeManager;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    SimulationWidget *getActiveSim() const;

    void configureTabWidget();

    void createGraphicObjects();
    void createPhysical();
    void createElectrostatic();

    bool openFile(QString filename);
    bool saveToFile(QString filename);

private slots:
    void redo();
    void undo();

    void copy();
    void cut();
    void paste();

    void askSaveToFile(bool override = true);
    void askOpenFiles();

    SimulationWidget *addSimulationTab();
    void removeTab(int idx);

    void showAbout() const;
    void updateActionsEnabled();
};
#endif // MAINWINDOW_H
