#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "physical/PhysicalObjectPtr.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createGraphicObjects();
    void createPhysical();
    void createElectrostatic();

    void setTo2D(const PhysicalObjectPtr &physical);

};
#endif // MAINWINDOW_H
