#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = ShiftSketchCore
TEMPLATE = lib

include("../../Eks/EksCore/GeneralOptions.pri")

INCLUDEPATH += $$ROOT/shift/GraphicsCore \
  $$ROOT/Eks/EksCore/include \
  $$ROOT/Eks/EksScript \
  $$ROOT/Eks/Eks3D/include \
  $$ROOT/Shift/ShiftCore/include \
  $$ROOT/Shift/SketchCore/include

LIBS += -lShiftCore -lEksCore -lEks3D -lEksScript -lGraphicsCore

SOURCES += src/SkGlobal.cpp \
    src/SkSketch.cpp \
    src/SkPoint.cpp \
    src/SkSolver.cpp \
    src/SkLine.cpp \
    src/SkAngle.cpp \
    src/SkDistance.cpp \
    src/SkConstraint.cpp

HEADERS += include/SkGlobal.h \
    include/SkSketch.h \
    include/SkPoint.h \
    include/SkSolver.h \
    include/SkLine.h \
    include/SkAngle.h \
    include/SkDistance.h \
    include/SkConstraint.h
