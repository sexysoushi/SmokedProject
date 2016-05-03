#ifndef RUBIKS_H
#define RUBIKS_H

#include "Shapes/cube.h"
#include "Object3D.h"

class Rubiks : public Object3D
{
public:
    Rubiks(int dim, float s);

    //void drawShape();

private:
    Cube* cube;

    int dimension;
    float spacing;
    double angle;
};

#endif // RUBIKS_H
