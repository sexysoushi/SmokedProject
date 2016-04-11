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

DESTDIR = release
OBJECTS_DIR = obj

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



HEADERS  += mainwindow.h \
    particle.h \
    Common/GlFramework.h \
    Common/GlWindow.h \
    Common/LF_String.h \
    Common/Object3D.h \
    Common/Shapes/Basis.h \
    Common/Shapes/cube.h \
    TP01.h

SOURCES += main.cpp\
        mainwindow.cpp \
    particle.cpp \
    Common/GlFramework.cpp \
    Common/GlWindow.cpp \
    Common/LF_String.cpp \
    Common/Object3D.cpp \
    Common/Shapes/Basis.cpp \
    Common/Shapes/cube.cpp \
    TP01.cpp
