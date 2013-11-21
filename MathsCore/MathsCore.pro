#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = MathsCore
TEMPLATE = lib

include("../../Eks/EksCore/GeneralOptions.pri")

HEADERS += \
    include/mcglobal.h \
    include/mcmathsoperation.h \
    include/mcimage.h \
    include/mcsource.h \
    include/mcsimpleadd.h \
    include/mcsimplemultiply.h \
    include/mcsimple.h

INCLUDEPATH += $$ROOT/shift/MathsCore/include $$ROOT/Eks/EksCore/include $$ROOT/Eks/EksScript $$ROOT/Shift/ShiftCore/include

LIBS += -lShiftCore -lEksCore -lEksScript

SOURCES += \
    src/mathscore.cpp \
    src/mcmathsoperation.cpp \
    src/mcimage.cpp \
    src/mcsource.cpp \
    src/mcsimpleadd.cpp \
    src/mcsimplemultiply.cpp \
    src/mcsimple.cpp




