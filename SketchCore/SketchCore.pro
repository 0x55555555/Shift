#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = ShiftSketchCore
TEMPLATE = lib

include("../../Eks/EksCore/GeneralOptions.pri")

INCLUDEPATH += $$ROOT/shift/GraphicsCore $$ROOT/Eks/EksCore/include $$ROOT/Eks/EksScript $$ROOT/Eks/Eks3D/include $$ROOT/Shift/ShiftCore/include

LIBS += -lShiftCore -lEksCore -lEks3D -lEksScript -lShiftGraphicsCore

SOURCES += SkGlobal.cpp \
    SkSketch.cpp \
    SkPoint.cpp \
    SkSolver.cpp \
    SkLine.cpp \
    SkAngle.cpp \
    SkDistance.cpp \
    SkConstraint.cpp

HEADERS += SkGlobal.h \
    SkSketch.h \
    SkPoint.h \
    SkSolver.h \
    SkLine.h \
    SkAngle.h \
    SkDistance.h \
    SkConstraint.h
