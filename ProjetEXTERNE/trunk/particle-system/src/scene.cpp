#include "scene.h"

Scene::Scene(Camera* camera)
{
    this->camera = camera;
}

Scene::~Scene()
{
    vector<SceneNode*>::iterator it;
    for(it = nodes.begin(); it != nodes.end(); ++it) {
        delete *it;
    }
    delete camera;
}

void Scene::addNode(SceneNode* node)
{
	nodes.push_back(node);
}

void Scene::removeNode()
{
	vector<SceneNode*>::iterator it;
	for(it = nodes.begin(); it != nodes.end(); ++it) {
		delete *it;
	}
}

Camera* Scene::getCamera()
{
    return camera;
}

vector<SceneNode*>::iterator Scene::begin() {
    return nodes.begin();
}

vector<SceneNode*>::iterator Scene::end() {
    return nodes.end();
}
