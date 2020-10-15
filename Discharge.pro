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
    gui/editor.cpp \
    gui/graphicobject.cpp \
    gui/historywidget.cpp \
    gui/modificatoreditor.cpp \
    gui/prototypemanager.cpp \
    gui/selectionmanager.cpp \
    gui/simulationgraphicobject.cpp \
    gui/simulationwidget.cpp \
    gui/simulationwidgetstate.cpp \
    gui/timecontrolwidget.cpp \
    gui/zoomwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    physical/Simulation.cpp \
    physical/SimulationState.cpp \
    physical/SimulationSubject.cpp \
    physical/modificators/ChargeExchangeModificator.cpp \
    physical/modificators/ClassicModificator.cpp \
    physical/modificators/ElectrostaticForceModificator.cpp \
    physical/modificators/ForceSensitiveModificator.cpp \
    physical/modificators/GravityForceModificator.cpp \
    physical/modificators/Modificator.cpp \
    physical/modificators/ModificatorFactory.cpp \
    physical/modificators/MovableModificator.cpp \
    physical/modificators/PhysicalCollisionModificator.cpp \
    toolbox/Savable.cpp \
    toolbox/SavableData.cpp \
    toolbox/matrix.cpp \
    toolbox/vector.cpp

HEADERS += \
    gui/attributeeditorwidget.h \
    gui/copymanager.h \
    gui/draggablegraphic.h \
    gui/editor.h \
    gui/graphicobject.h \
    gui/historywidget.h \
    gui/modificatoreditor.h \
    gui/prototypemanager.h \
    gui/selectionmanager.h \
    gui/simulationgraphicobject.h \
    gui/simulationwidget.h \
    gui/simulationwidgetstate.h \
    gui/timecontrolwidget.h \
    gui/zoomwidget.h \
    mainwindow.h \
    physical/PhysicalConstants.h \
    physical/RealNumber.h \
    physical/Simulation.h \
    physical/SimulationState.h \
    physical/SimulationSubject.h \
    physical/SimulationSubjectPtr.h \
    physical/modificators/ChargeExchangeModificator.h \
    physical/modificators/ClassicModificator.h \
    physical/modificators/ElectrostaticForceModificator.h \
    physical/modificators/ForceSensitiveModificator.h \
    physical/modificators/GravityForceModificator.h \
    physical/modificators/Modificator.h \
    physical/modificators/ModificatorFactory.h \
    physical/modificators/MovableModificator.h \
    physical/modificators/PhysicalCollisionModificator.h \
    toolbox/Savable.h \
    toolbox/SavableData.h \
    toolbox/Unused.h \
    toolbox/history.h \
    toolbox/matrix.h \
    toolbox/matrixexception.h \
    toolbox/vector.h

FORMS += \
    gui/historywidget.ui \
    gui/modificatoreditor.ui \
    gui/simulationwidget.ui \
    gui/timecontrolwidget.ui \
    gui/zoomwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
