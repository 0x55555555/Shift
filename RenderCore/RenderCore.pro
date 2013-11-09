#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T15:56:15
#
#-------------------------------------------------
TARGET = ShiftRenderCore
TEMPLATE = lib

QT += opengl

include("../../Eks/EksCore/GeneralOptions.pri")

INCLUDEPATH += $$ROOT/shift $$ROOT/shift/RenderCore $$ROOT/Eks/EksCore/include $$ROOT/Eks/EksScript $$ROOT/Eks/Eks3D/include $$ROOT/Shift/ShiftCore/include

LIBS += -lShiftCore -lEksCore -lEks3D -lEksScript

SOURCES += \
    RCViewport.cpp \
    RCTransform.cpp \
    RCTexture.cpp \
    RCScene.cpp \
    RCRenderable.cpp \
    RCGlobal.cpp \
    RCGeometry.cpp \
    RCCamera.cpp \
    Shader/RCShadingGroup.cpp \
    Shader/RCShaderDataBindings.cpp \
    Shader/RCShader.cpp \
    Targets/RCTextureRenderTarget.cpp \
    Targets/RCScreenRenderTarget.cpp \
    Targets/RCRenderTarget.cpp \
    Utilities/RCBaseProperties.cpp

HEADERS += \
    RCViewport.h \
    RCTransform.h \
    RCTexture.h \
    RCScene.h \
    RCRenderable.h \
    RCGlobal.h \
    RCGeometry.h \
    RCCamera.h \
    Shader/RCShadingGroup.h \
    Shader/RCShaderDataBindings.h \
    Shader/RCShader.h \
    Targets/RCTextureRenderTarget.h \
    Targets/RCScreenRenderTarget.h \
    Targets/RCRenderTarget.h \
    Utilities/RCBaseProperties.h






