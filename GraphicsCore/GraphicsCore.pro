#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = ShiftGraphicsCore
TEMPLATE = lib

QT += opengl

include("../../Eks/EksCore/GeneralOptions.pri")

HEADERS += GCGlobal.h \
    UI/NodeGraph/GCShiftRenderModel.h \
    UI/NodeGraph/GCAbstractNodeDelegate.h \
    UI/NodeGraph/GCNodeController.h \
    Utilities/GCComposeTransform.h \
    Utilities/GCComposeVector3.h \
    Manipulators/GCManipulator.h \
    Manipulators/GCButtonManipulator.h \
    Manipulators/GCDistanceManipulator.h \
    Manipulators/GCTranslateManipulator.h \
    Manipulators/GCRotateManipulator.h \
    Manipulators/GCManipulatable.h \
    Manipulators/GCManipulatorHelpers.h \
    2D/GCPlate.h \
    2D/GCCameraAlignedPlate.h \
    2D/GCElement.h \
    2D/GCProject3D.h \
    UI/GCSceneExplorer.h \
    GCManipulatableScene.h

INCLUDEPATH += $$ROOT/shift $$ROOT/shift/GraphicsCore $$ROOT/Eks/EksCore/include $$ROOT/Eks/EksScript $$ROOT/Eks/Eks3D/include $$ROOT/Shift/ShiftCore/include

LIBS += -lShiftCore -lEksCore -lEks3D -lEksScript -lShiftMathsCore -lShiftRenderCore

SOURCES += \
    UI/NodeGraph/GCShiftRenderModel.cpp \
    UI/NodeGraph/GCAbstractNodeDelegate.cpp \
    UI/NodeGraph/GCNodeController.cpp \
    Manipulators/GCManipulator.cpp \
    Manipulators/GCButtonManipulator.cpp \
    Manipulators/GCDistanceManipulator.cpp \
    Manipulators/GCTranslateManipulator.cpp \
    Manipulators/GCRotateManipulator.cpp \
    Manipulators/GCManipulatable.cpp \
    Utilities/GCComposeTransform.cpp \
    Utilities/GCComposeVector3.cpp \
    GCGlobal.cpp \
    2D/GCPlate.cpp \
    2D/GCCameraAlignedPlate.cpp \
    2D/GCElement.cpp \
    2D/GCProject3D.cpp \
    UI/GCSceneExplorer.cpp \
    GCManipulatableScene.cpp






