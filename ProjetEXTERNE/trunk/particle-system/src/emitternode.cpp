#include "emitternode.h"

EmitterNode::EmitterNode(RenderFramework* framework)
    : ModelNode(framework, NULL)
{
    Shader *emitShader = new Shader("linear_emitter");

    map<string, BufferAttribute> attributes = framework->getShaderManager()->getDefaultAttributes();

    attributes.insert(pair<string, BufferAttribute>("velocity", VELOCITY_BUFFER));
    attributes.insert(pair<string, BufferAttribute>("delay", DELAY_BUFFER));
    attributes.insert(pair<string, BufferAttribute>("lifetime", LIFETIME_BUFFER));

    emitShader->init(attributes);

    framework->getShaderManager()->addShader(emitShader);

    this->mesh = new Mesh(emitShader, GL_POINTS);
    this->texture = new Texture("particleTexture.png", "tex");
    this->texture->init();
}

EmitterNode::~EmitterNode()
{
    delete texture;
}

void EmitterNode::init()
{
    int nbParticles = 100000;

    EmitterVertexData* emitterData = new EmitterVertexData[nbParticles];

    float maxLifetime = 10.0;
    float maxVel = 10.0;
    float minVel = 1.0;

    ConeSampler sampler(Vec3(0.0, 1.0, 0.0), Vec2(radians(20), radians(20)));
    ColorSampler colorSampler;

    for(int i = 0; i < nbParticles; ++i) {
        float vel = rand_0_1() * (maxVel - minVel) + minVel;

        emitterData[i].position = Vec3(0.0);
        emitterData[i].velocity = sampler.getSample() * vel;
        emitterData[i].color = colorSampler.getSample();
        emitterData[i].lifetime = rand_0_1() * maxLifetime;
        emitterData[i].delay = rand_0_1();
    }

    vector<VertexBufferDataInfo> dataInfos;

    GLsizei stride = sizeof(EmitterVertexData);

    for(int i = 0; i < 3; ++i) {
        VertexBufferDataInfo info;
        switch(i) {
            case 0: info.attributeType = VERTEX_BUFFER; break;
            case 1: info.attributeType = COLOUR_BUFFER; break;
            case 2: info.attributeType = VELOCITY_BUFFER; break;
        }
        info.offset = i * sizeof(Vec3);
        info.dataType = GL_FLOAT;
        info.size = 3;
        dataInfos.push_back(info);
    }

    for(int i = 0; i < 2; ++i) {
        VertexBufferDataInfo info;
        switch(i) {
            case 0: info.attributeType = DELAY_BUFFER; break;
            case 1: info.attributeType = LIFETIME_BUFFER; break;
        }
        info.offset = 3 * sizeof(Vec3) + i * sizeof(float);
        info.dataType = GL_FLOAT;
        info.size = 1;
        dataInfos.push_back(info);
    }

    mesh->createInterleavedBufferData(dataInfos, emitterData,
                                      nbParticles * sizeof(EmitterVertexData), GL_STATIC_DRAW, stride);

    delete[] emitterData;
}

void EmitterNode::sendUniforms(Shader *material)
{
    material->sendUniform(texture->getName(), texture);
}

void EmitterNode::preRender()
{
    this->texture->bind();
    glDepthMask(GL_FALSE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void EmitterNode::postRender()
{
    this->texture->unBind();
    glDepthMask(GL_TRUE);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
}
