#ifndef SHAPE_H
#define SHAPE_H
#include "Common/Object3D.h"


class Shape : Object3D
{
public:
    Shape();

protected:
    virtual void drawShape() = 0;
};

#endif // SHAPE_H
