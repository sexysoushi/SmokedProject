#ifndef APP_H
#define APP_H

#include "GL/glew.h"

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <iostream>
#include "renderer.h"
#include "scene.h"
#include "shadermanager.h"
#include "scenebuilder.h"

class App : public QGLWidget
{
	Q_OBJECT

private:
    Renderer* renderer;
    Scene* scene;
    QElapsedTimer timer;
    ShaderManager* shaderManager;
    QPoint lastCursorPos;
    bool isCapturingCursor;

    void initShaders();
    void initGlew();

public:
	explicit App(QWidget *parent = 0);
    ~App();

	void init();

	void changeEmitter(int type);

    void paintGL();
    void timerEvent(QTimerEvent *);
    void resizeGL(int w, int h);
    void initializeGL();
    void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent* event);
};

#endif // APP_H
