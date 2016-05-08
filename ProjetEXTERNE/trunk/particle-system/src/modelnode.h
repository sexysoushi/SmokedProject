#ifndef MODELNODE_H
#define MODELNODE_H

#include <vector>
#include "scenenode.h"
#include "renderframework.h"
#include "shadermanager.h"
#include "mesh.h"

class ModelNode : public SceneNode
{
private:
    bool visible;
    vector<ModelNode*> children;

protected:
    virtual void sendUniforms(Shader* material) = 0;
    void sendDefaultUniforms(Shader* material);

    RenderFramework *framework;
    Mesh *mesh;

public:
    ModelNode(RenderFramework *framework, Mesh *mesh);
    ModelNode(RenderFramework* framework, Mesh* mesh, Vec3 position, Quaternion orientation);
    ~ModelNode();

    void setVisible(bool visible);
    void addChild(ModelNode *child);
    void visit();

    virtual void preRender() {}
    virtual void postRender() {}
};

#endif // MODELNODE_H
