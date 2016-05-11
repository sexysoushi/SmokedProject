#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T02:31:46
#
#-------------------------------------------------

CONFIG += console release
QT += core gui opengl
TARGET = SmokedProject
TEMPLATE = app

DEPENDPATH += SmokedProject
INCLUDEPATH = Common/ "../glew-mingw\include"
win32:LIBS += -L"../glew-mingw\lib" -lglew32
unix:LIBS+= -lGL -lGLEW

DESTDIR = release
OBJECTS_DIR = obj

HEADERS  += mainwindow.h \
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
    GlFrame.h \
    particlesystem.h

SOURCES += main.cpp\
        mainwindow.cpp \
    Common/GlFramework.cpp \
    Common/GlWindow.cpp \
    Common/LF_String.cpp \
    Common/Object3D.cpp \
    Common/Shapes/Basis.cpp \
    Common/RandomNumberGenerator.cpp \
    GlFrame.cpp \
    particlesystem.cpp


DISTFILES += \
    Shaders/color.fs \
    Shaders/color.vs \
    Shaders/PerVertex.fs \
    Shaders/PerVertex.vs
