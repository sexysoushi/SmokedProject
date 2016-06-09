#ifndef QIMAGETEST_H
#define QIMAGETEST_H
#include "Common/GlFramework.h"
#include "Common/Object3D.h"
#include <QImage>
#include <QGLWidget>

class QImageTest : public Object3D
{
private:
    QImage t;
    QImage b;

    GLint tc;

public:
    QImageTest();

    void loadGLTextures();
    void closeGLTextures();

protected:
    GLuint texId;
    void drawShape();
};

#endif // QIMAGETEST_H
