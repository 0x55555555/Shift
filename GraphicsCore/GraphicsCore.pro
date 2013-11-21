#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = GraphicsCore
TEMPLATE = lib

QT += opengl

include("../../Eks/EksCore/GeneralOptions.pri")

HEADERS += include/GCGlobal.h \
    include/UI/NodeGraph/GCShiftRenderModel.h \
    include/UI/NodeGraph/GCAbstractNodeDelegate.h \
    include/UI/NodeGraph/GCNodeController.h \
    include/Utilities/GCComposeTransform.h \
    include/Utilities/GCComposeVector3.h \
    include/Manipulators/GCManipulator.h \
    include/Manipulators/GCButtonManipulator.h \
    include/Manipulators/GCDistanceManipulator.h \
    include/Manipulators/GCTranslateManipulator.h \
    include/Manipulators/GCRotateManipulator.h \
    include/Manipulators/GCManipulatable.h \
    include/Manipulators/GCManipulatorHelpers.h \
    include/2D/GCPlate.h \
    include/2D/GCCameraAlignedPlate.h \
    include/2D/GCElement.h \
    include/2D/GCProject3D.h \
    include/UI/GCSceneExplorer.h \
    include/GCManipulatableScene.h

INCLUDEPATH += $$ROOT/shift $$ROOT/shift/GraphicsCore $$ROOT/Eks/EksCore/include $$ROOT/Eks/EksScript $$ROOT/Eks/Eks3D/include $$ROOT/Shift/ShiftCore/include

LIBS += -lShiftCore -lEksCore -lEks3D -lEksScript -lShiftMathsCore -lShiftRenderCore

SOURCES += \
    src/UI/NodeGraph/GCShiftRenderModel.cpp \
    src/UI/NodeGraph/GCAbstractNodeDelegate.cpp \
    src/UI/NodeGraph/GCNodeController.cpp \
    src/Manipulators/GCManipulator.cpp \
    src/Manipulators/GCButtonManipulator.cpp \
    src/Manipulators/GCDistanceManipulator.cpp \
    src/Manipulators/GCTranslateManipulator.cpp \
    src/Manipulators/GCRotateManipulator.cpp \
    src/Manipulators/GCManipulatable.cpp \
    src/Utilities/GCComposeTransform.cpp \
    src/Utilities/GCComposeVector3.cpp \
    src/GCGlobal.cpp \
    src/2D/GCPlate.cpp \
    src/2D/GCCameraAlignedPlate.cpp \
    src/2D/GCElement.cpp \
    src/2D/GCProject3D.cpp \
    src/UI/GCSceneExplorer.cpp \
    src/GCManipulatableScene.cpp






