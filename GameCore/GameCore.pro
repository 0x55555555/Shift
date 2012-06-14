#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = ShiftGameCore
TEMPLATE = lib

include("../../Eks/EksCore/GeneralOptions.pri")

INCLUDEPATH += $$ROOT/shift/GraphicsCore $$ROOT/Eks/EksCore $$ROOT/Eks/EksScript $$ROOT/Eks/Eks3D/include $$ROOT/Shift

LIBS += -lshift -lEksCore -lEks3D -lEksScript

SOURCES += GAGlobal.cpp \
    GAPlotPoint.cpp \
    GAPlotCondition.cpp \
    GAAutoCompletePlotPoint.cpp

HEADERS += GAGlobal.h \
    GAPlotPoint.h \
    GAPlotCondition.h \
    GAAutoCompletePlotPoint.h
