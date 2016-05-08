#include "scenebuilder.h"

void SceneBuilder::buildScene(Scene *scene, RenderFramework *framework)
{	
	EmitterNode *emitNode = new EmitterNode(framework);
	emitNode->init();
	scene->addNode(emitNode);
}

void SceneBuilder::changeScene(Scene *scene, RenderFramework *framework, int emitterType)
{
	scene->removeNode();

	switch(emitterType) {
	case 0:
	case 1: {
		EmitterNode *emitNode = new EmitterNode(framework);
		emitNode->init();
		scene->addNode(emitNode);
		break;
	}

	case 2: {
		WaveParticlesNode *waveParticles = new WaveParticlesNode(framework);
		waveParticles->init();
		scene->addNode(waveParticles);
		break;
	}
	}
}


