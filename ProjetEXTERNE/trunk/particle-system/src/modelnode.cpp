#include "modelnode.h"

ModelNode::ModelNode(RenderFramework* framework, Mesh* mesh)
    : SceneNode(Vec3(0.0), Quaternion(0.0, Vec3(1.0, 0.0, 0.0)))
{
    this->visible = true;
    this->mesh = mesh;
    this->framework = framework;
}

ModelNode::ModelNode(RenderFramework* framework, Mesh* mesh, Vec3 position, Quaternion orientation)
    : SceneNode(position, orientation)
{
    this->visible = true;
    this->mesh = mesh;
    this->framework = framework;
}

ModelNode::~ModelNode()
{
    delete mesh;
}

void ModelNode::sendDefaultUniforms(Shader *material)
{
    material->sendUniform("mvp", framework->getMVP().transpose());
    material->sendUniform("time", framework->getTime());
}

void ModelNode::setVisible(bool visible)
{
    this->visible = visible;
}

void ModelNode::addChild(ModelNode* child)
{
    children.push_back(child);
}

void ModelNode::visit()
{
    if(!visible)
        return;

    framework->pushMatrix(getTransform());

    vector<ModelNode*>::iterator it;
    for(it = children.begin(); it != children.end(); ++it) {
        (*it)->visit();
    }

    Shader *mat = mesh->getMaterial();

    if(mat == NULL) {
        mat = framework->getShaderManager()->getShader("default");
    }

    // use current shader
    mat->use();

    // send the default uniforms
    sendDefaultUniforms(mat);

    // inner send uniforms
    sendUniforms(mat);

    // draw the mesh
    preRender();
    mesh->draw();
    postRender();

    // unuse current shader
    mat->release();

    framework->popMatrix();
}
