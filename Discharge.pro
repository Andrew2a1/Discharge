QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/draggablegraphic.cpp \
    gui/graphicobject.cpp \
    gui/historywidget.cpp \
    gui/simulationgraphicobject.cpp \
    gui/simulationwidget.cpp \
    gui/simulationwidgetstate.cpp \
    gui/timecontrolwidget.cpp \
    gui/zoomwidget.cpp \
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
    gui/draggablegraphic.h \
    gui/graphicobject.h \
    gui/historywidget.h \
    gui/simulationgraphicobject.h \
    gui/simulationwidget.h \
    gui/simulationwidgetstate.h \
    gui/timecontrolwidget.h \
    gui/zoomwidget.h \
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
    toolbox/history.h \
    toolbox/matrix.h \
    toolbox/matrixexception.h \
    toolbox/vector.h

FORMS += \
    gui/historywidget.ui \
    gui/simulationwidget.ui \
    gui/timecontrolwidget.ui \
    gui/zoomwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
