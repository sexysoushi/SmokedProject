#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"


class Cube : public Object3D
{

public:
    Cube(GLfloat size);

protected:
    void drawShape();

    private:
    GLfloat m_TabVertices[8*3];

};


#endif // CUBE_H
