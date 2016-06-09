#ifndef SKYBOX_H
#define SKYBOX_H
#include "Common/GlFramework.h"
#include "Common/Object3D.h"
#include "Common/Vectors.h"
#include <QImage>
#include <QGLWidget>

class Skybox : public Object3D
{

public:
    Skybox();
    void drawSkybox();
    void loadGLTextures();

protected:
    void drawShape();

private:
    //texture top
    QImage t_top;
    QImage b1;
    //texture front
    QImage t_front;
    QImage b2;
    //texture right
    QImage t_right;
    QImage b3;
    //texture left
    QImage t_left;
    QImage b4;
    //texture bottom
    QImage t_bottom;
    QImage b5;
    //texture back
    QImage t_back;
    QImage b6;

    //shader
    Vec2* texCoord;

};

#endif // SKYBOX_H
