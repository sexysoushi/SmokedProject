#ifndef EMITTERNODE_H
#define EMITTERNODE_H

#include "texture.h"
#include "modelnode.h"
#include "conesampler.h"
#include "color.h"
#include "colorsampler.h"

struct EmitterVertexData {
    Vec3 position;
    Color color;
    Vec3 velocity;
    float delay;
    float lifetime;
};

class EmitterNode : public ModelNode
{
    private:
        Texture *texture;
    public:
        EmitterNode(RenderFramework* framework);
        ~EmitterNode();

        /**
         * Compute default attributes of his mesh's shader
         */
        void init();

        /**
         * Send all of his "uniforms" to his own mesh's shader
         */
        void sendUniforms(Shader* material);
        void preRender();
        void postRender();

};

#endif // EMITTERNODE_H
