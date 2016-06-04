#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T02:31:46
#
#-------------------------------------------------

CONFIG += console c++11 debug release
QT += core gui opengl
TARGET = SmokedProject
TEMPLATE = app

DEPENDPATH += SmokedProject
INCLUDEPATH = Common/ "../glew-mingw\include"
win32:LIBS += -L"../glew-mingw\lib" -lglew32
unix:LIBS+= -lGL -lGLEW

DESTDIR = release
OBJECTS_DIR = obj

HEADERS  += \
    src/Common/GlFramework.h \
    src/Common/GlWindow.h \
    src/Common/LF_String.h \
    src/Common/Object3D.h \
    src/Common/Shapes/Basis.h \
    src/Common/AbstractFramework.h \
    src/Common/MemDefns.h \
    src/Common/RandomNumberGenerator.h \
    src/Common/Types.h \
    src/Common/Vectors.h \
    src/particlesystem.h \
    src/Common/Shapes/cube.h \
    src/Quaternion.h \
    src/Camera.h \
    src/mainwindow.h \
    src/glframe.h

SOURCES += src/main.cpp\
    src/Common/GlFramework.cpp \
    src/Common/GlWindow.cpp \
    src/Common/LF_String.cpp \
    src/Common/Object3D.cpp \
    src/Common/Shapes/Basis.cpp \
    src/Common/RandomNumberGenerator.cpp \
    src/particlesystem.cpp \
    src/Common/Shapes/cube.cpp \
    src/Quaternion.cpp \
    src/Camera.cpp \
    src/mainwindow.cpp \
    src/glframe.cpp


DISTFILES += \
    Shaders/color.fs \
    Shaders/color.vs \
    Shaders/PerVertex.fs \
    Shaders/PerVertex.vs \
    Shaders/Tornade.vs \
    Shaders/Tornade.fs \
    Shaders/Texture.vs \
    Shaders/Texture.fs \
    Shaders/Firework.vs \
    Shaders/Firework.fs \
    Shaders/DamierTexture.vs \
    Shaders/DamierTexture.fs \
    Shaders/Atome.vs \
    Shaders/Atome.fs

OTHER_FILES += \
    release/Shaders/Tornade.vs \
    release/Shaders/Tornade.fs \
    release/Shaders/Texture.vs \
    release/Shaders/Texture.fs \
    release/Shaders/PerVertex.vs \
    release/Shaders/PerVertex.fs \
    release/Shaders/Firework.vs \
    release/Shaders/Firework.fs \
    release/Shaders/DamierTexture.vs \
    release/Shaders/DamierTexture.fs \
    release/Shaders/color.vs \
    release/Shaders/color.fs \
    release/Shaders/Atome.vs \
    release/Shaders/Atome.fs

