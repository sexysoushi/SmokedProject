#ifndef TEXTURE_H
#define TEXTURE_H
#include "Common/Object3D.h"

class Texture : public Object3D
{
public:
    Texture();
    void initGLFrame();
    void closeGLFrame();
private:
    GLint tc;
protected:
    unsigned char * image;
    int imageWidth;
    int imageHeight;

    GLuint texID;
    GLfloat texCoordinates[4*2];

};

#endif // TEXTURE_H
