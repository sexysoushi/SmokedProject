#ifndef TEXTURE_H
#define TEXTURE_H

//#include "Common/AbstractFramework.h"
#include <GL/glew.h>
#include <QGLWidget>
#include <QImage>

class Texture
{
public:
    Texture();

    static GLuint loadTexture(char* t);
};

#endif // TEXTURE_H
