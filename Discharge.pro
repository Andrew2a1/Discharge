QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/simulationwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    physical/ChargeModifier.cpp \
    physical/ElectricCharge.cpp \
    physical/PhysicalMemento.cpp \
    physical/PhysicalModifier.cpp \
    physical/PhysicalObject.cpp \
    physical/Simulation.cpp \
    physical/SimulationState.cpp \
    toolbox/matrix.cpp \
    toolbox/vector.cpp

HEADERS += \
    gui/simulationwidget.h \
    mainwindow.h \
    physical/ChargeModifier.h \
    physical/ChargeState.h \
    physical/ElectricCharge.h \
    physical/PhysicalMemento.h \
    physical/PhysicalModifier.h \
    physical/PhysicalObject.h \
    physical/PhysicalState.h \
    physical/Simulation.h \
    physical/SimulationState.h \
    toolbox/matrix.h \
    toolbox/matrixexception.h \
    toolbox/vector.h

FORMS += \
    gui/simulationwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
