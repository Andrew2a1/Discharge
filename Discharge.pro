QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/attributeeditorwidget.cpp \
    gui/copymanager.cpp \
    gui/draggablegraphic.cpp \
    gui/electrostaticgraphicobject.cpp \
    gui/graphicobject.cpp \
    gui/historywidget.cpp \
    gui/physicalgraphicobject.cpp \
    gui/prototypemanager.cpp \
    gui/selectionmanager.cpp \
    gui/simulationgraphicobject.cpp \
    gui/simulationwidget.cpp \
    gui/simulationwidgetstate.cpp \
    gui/timecontrolwidget.cpp \
    gui/zoomwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    physical/ElectricCharge.cpp \
    physical/PhysicalObject.cpp \
    physical/Simulation.cpp \
    physical/SimulationState.cpp \
    toolbox/Savable.cpp \
    toolbox/SavableData.cpp \
    toolbox/matrix.cpp \
    toolbox/vector.cpp

HEADERS += \
    gui/attributeeditorwidget.h \
    gui/copymanager.h \
    gui/draggablegraphic.h \
    gui/electrostaticgraphicobject.h \
    gui/graphicobject.h \
    gui/historywidget.h \
    gui/physicalgraphicobject.h \
    gui/prototypemanager.h \
    gui/selectionmanager.h \
    gui/simulationgraphicobject.h \
    gui/simulationwidget.h \
    gui/simulationwidgetstate.h \
    gui/timecontrolwidget.h \
    gui/zoomwidget.h \
    mainwindow.h \
    physical/ElectricCharge.h \
    physical/PhysicalConstants.h \
    physical/PhysicalObject.h \
    physical/PhysicalObjectPtr.h \
    physical/Simulation.h \
    toolbox/Savable.h \
    toolbox/SavableData.h \
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
