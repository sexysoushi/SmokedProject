#ifndef TEXTURE_H
#define TEXTURE_H

//#include "Common/AbstractFramework.h"
#include <GL/glew.h>
#include <QGLWidget>
#include <QImage>

// static class to load textures from filePath

class Texture
{
    public:
        static GLuint loadTexture(char* t);
};

#endif // TEXTURE_H
