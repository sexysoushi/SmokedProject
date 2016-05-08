#ifndef RENDERFRAMEWORK_H
#define RENDERFRAMEWORK_H

#include "math/matrix4.h"
#include "shadermanager.h"

class RenderFramework
{
public:
    RenderFramework() {}

    virtual ~RenderFramework() {}

    virtual void pushMatrix(const Matrix4& mat) = 0;

    virtual void popMatrix() = 0;

    virtual Matrix4 getMVP() const = 0;

    virtual float getTime() const = 0;

    virtual ShaderManager* getShaderManager() const = 0;
};

#endif // RENDERFRAMEWORK_H
