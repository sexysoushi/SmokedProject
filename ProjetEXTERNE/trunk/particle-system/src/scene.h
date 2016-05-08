#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "scenenode.h"
#include "camera.h"

using namespace std;

class Scene
{
private:
    vector<SceneNode*> nodes;
    Camera* camera;
public:
    Scene(Camera* camera);
    ~Scene();

    void addNode(SceneNode* node);
	void removeNode();
    Camera* getCamera();

    vector<SceneNode*>::iterator begin();
    vector<SceneNode*>::iterator end();
};

#endif // SCENE_H
