CONFIG += console release
QT += core gui opengl widgets
TARGET = ParticleSystem
TEMPLATE = app

DEPENDPATH += src

win32 {
    INCLUDEPATH = src "../lib/glew-mingw/include"
    LIBS += -L"..\lib\glew-mingw\lib" -lglew32
}

unix:!macx {
	INCLUDEPATH = src "../lib/glew-unix/include"
	LIBS += -L"../lib/glew-unix/lib" -lGLEW
}

macx {
	INCLUDEPATH = src "../lib/glew-osx/include"
	LIBS += -L"../lib/glew-osx/lib" -lGLEW
}

DESTDIR = ../build/
OBJECTS_DIR = ../build/obj

# Input
HEADERS += \
    src/app.h \
    src/math/matrix3.h \
    src/math/matrix4.h \
    src/math/vec2.h \
    src/math/vec3.h \
    src/math/vec4.h \
    src/math/mathshelpers.h \
    src/math/quaternion.h \
    src/renderer.h \
    src/renderframework.h \
    src/matrixstack.h \
    src/shader.h \
    src/scene.h \
    src/scenenode.h \
	src/modelnode.h \
    src/mesh.h \
    src/shadermanager.h \
	src/bufferattribute.h \
	src/camera.h \
    src/emitternode.h \
    src/scenebuilder.h \
	src/waveparticlesnode.h \
    src/texture.h \
    src/conesampler.h \
	src/sampler.h \
	src/window.h \
    src/color.h \
    src/colorsampler.h

SOURCES += \
    src/app.cpp \
    src/main.cpp \
    src/math/matrix3.cpp \
    src/math/matrix4.cpp \
    src/math/vec2.cpp \
    src/math/vec3.cpp \
    src/math/quaternion.cpp \
    src/renderer.cpp \
    src/shader.cpp \
    src/scene.cpp \
    src/scenenode.cpp \
	src/modelnode.cpp \
    src/mesh.cpp \
	src/shadermanager.cpp \
	src/camera.cpp \
    src/emitternode.cpp \
    src/scenebuilder.cpp \
	src/waveparticlesnode.cpp \
    src/texture.cpp \
	src/conesampler.cpp \
    src/window.cpp \
    src/colorsampler.cpp

FORMS += \
    src/window.ui

OTHER_FILES += \
    ../build/shaders/default.frag \
    ../build/shaders/default.vert \
    ../build/shaders/linear_emitter.vert \
    ../build/shaders/linear_emitter.frag \
    ../build/shaders/waves.frag \
    ../build/shaders/waves.vert \
    ../build/data/particleTexture.png


macx {
        ShaderFiles.files = ../build/shaders/default.vert \
                            ../build/shaders/default.frag \
                            ../build/shaders/linear_emitter.vert \
                            ../build/shaders/linear_emitter.frag \
                            ../build/shaders/waves.vert \
                            ../build/shaders/waves.frag
        ShaderFiles.path = Contents/MacOS/shaders
        QMAKE_BUNDLE_DATA += ShaderFiles

        MediaFiles.files = ../build/data/particleTexture.png
        MediaFiles.path = Contents/MacOS/data
        QMAKE_BUNDLE_DATA += MediaFiles
}
