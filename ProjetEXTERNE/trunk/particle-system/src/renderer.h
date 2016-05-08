#ifndef RENDERER_H
#define RENDERER_H

#include "renderframework.h"
#include "matrixstack.h"
#include "scene.h"
#include "modelnode.h"
#include "shadermanager.h"

class Renderer : public RenderFramework
{
private:
    MatrixStack<Matrix4> stack;
    Scene *scene;
    ShaderManager *shaderManager;
    float time;

public:
    Renderer(Scene* scene, ShaderManager* shaderManager);
    ~Renderer();

    void pushMatrix(const Matrix4& mat);
    void popMatrix();
    Matrix4 getMVP() const;
    float getTime() const;
    ShaderManager* getShaderManager() const;
    void render(float time);
};

#endif // RENDERER_H
