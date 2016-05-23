#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T02:31:46
#
#-------------------------------------------------

CONFIG += console release c++11
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
    Common/GlFramework.h \
    Common/GlWindow.h \
    Common/LF_String.h \
    Common/Object3D.h \
    Common/Shapes/Basis.h \
    Common/AbstractFramework.h \
    Common/MemDefns.h \
    Common/RandomNumberGenerator.h \
    Common/Types.h \
    Common/Vectors.h \
    particlesystem.h \
    Common/Shapes/cube.h \
    Quaternion.h \
    Camera.h \
    mainwindow.h \
    glframe.h \
    parameterswidget.h

SOURCES += main.cpp\
    Common/GlFramework.cpp \
    Common/GlWindow.cpp \
    Common/LF_String.cpp \
    Common/Object3D.cpp \
    Common/Shapes/Basis.cpp \
    Common/RandomNumberGenerator.cpp \
    particlesystem.cpp \
    Common/Shapes/cube.cpp \
    Quaternion.cpp \
    Camera.cpp \
    mainwindow.cpp \
    glframe.cpp \
    parameterswidget.cpp


DISTFILES += \
    Shaders/color.fs \
    Shaders/color.vs \
    Shaders/PerVertex.fs \
    Shaders/PerVertex.vs

OTHER_FILES += \
    release/Shaders/color.vs \
    release/Shaders/color.fs \
    release/Shaders/PerVertex.fs \
    release/Shaders/PerVertex.vs

FORMS +=
