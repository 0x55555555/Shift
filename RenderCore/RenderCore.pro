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
    src/RCViewport.cpp \
    src/RCTransform.cpp \
    src/RCTexture.cpp \
    src/RCScene.cpp \
    src/RCRenderable.cpp \
    src/RCGlobal.cpp \
    src/RCGeometry.cpp \
    src/RCCamera.cpp \
    src/Shader/RCShadingGroup.cpp \
    src/Shader/RCShaderDataBindings.cpp \
    src/Shader/RCShader.cpp \
    src/Targets/RCTextureRenderTarget.cpp \
    src/Targets/RCScreenRenderTarget.cpp \
    src/Targets/RCRenderTarget.cpp \
    src/Utilities/RCBaseProperties.cpp

HEADERS += \
    include/RCViewport.h \
    include/RCTransform.h \
    include/RCTexture.h \
    include/RCScene.h \
    include/RCRenderable.h \
    include/RCGlobal.h \
    include/RCGeometry.h \
    include/RCCamera.h \
    include/Shader/RCShadingGroup.h \
    include/Shader/RCShaderDataBindings.h \
    include/Shader/RCShader.h \
    include/Targets/RCTextureRenderTarget.h \
    include/Targets/RCScreenRenderTarget.h \
    include/Targets/RCRenderTarget.h \
    include/Utilities/RCBaseProperties.h






