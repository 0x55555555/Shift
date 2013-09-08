#-------------------------------------------------
#
# Project created by QtCreator 2013-02-21T09:02:34
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

include("../../../Eks/EksCore/GeneralOptions.pri")

TARGET = SketchCoreTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    sketchtest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$ROOT/shift/GraphicsCore \
    $$ROOT/Eks/EksCore/include \
    $$ROOT/Eks/Eks3D/include \
    $$ROOT/Eks/EksScript \
    $$ROOT/Shift/ShiftCore/include \
    $$ROOT/Shift/SketchCore

LIBS += -lShiftCore -lEksCore -lEks3D -lEksScript -lShiftGraphicsCore -lShiftSketchCore

HEADERS += \
    sketchtest.h
