#include "renderer.h"

Renderer::Renderer(Scene *scene, ShaderManager* shaderManager)
{
    this->shaderManager = shaderManager;
    this->scene = scene;
}

Renderer::~Renderer()
{

}

void Renderer::pushMatrix(const Matrix4& mat)
{
    stack.push(mat);
}

void Renderer::popMatrix()
{
    stack.pop();
}

ShaderManager* Renderer::getShaderManager() const
{
    return shaderManager;
}

Matrix4 Renderer::getMVP() const
{
    Matrix4 mvp;

    try {
        Matrix4 view = scene->getCamera()->getViewMatrix();
        Matrix4 projection = scene->getCamera()->getProjectionMatrix();
        Matrix4 model = stack.top();
        mvp = projection * view * model;
    } catch(const exception& e) {
        cerr << e.what() << endl;
    }

    return mvp;
}

float Renderer::getTime() const
{
    return time;
}

void Renderer::render(float time)
{
    this->time = time;

    pushMatrix(Matrix4::identity());

    vector<SceneNode*>::const_iterator it;
    for(it = scene->begin(); it != scene->end(); ++it) {
        ModelNode* node = static_cast<ModelNode*>(*it);

        if(node) {
            node->visit();
        }
    }

    popMatrix();
}
