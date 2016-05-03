#include "waveparticlesnode.h"

WaveParticlesNode::WaveParticlesNode(RenderFramework* framework)
    : ModelNode(framework, NULL)
{
    Shader *wavesShader = new Shader("waves");

    map<string, BufferAttribute> attributes = framework->getShaderManager()->getDefaultAttributes();

    attributes.insert(pair<string, BufferAttribute>("offset", OFFSET_BUFFER));
    wavesShader->init(attributes);
    framework->getShaderManager()->addShader(wavesShader);

    this->mesh = new Mesh(wavesShader, GL_LINES);
    this->areaWidth = 100;
}

WaveParticlesNode::~WaveParticlesNode()
{

}

void WaveParticlesNode::init()
{
    int nbParticles = areaWidth * areaWidth;

    WaveParticlesVertexData* waveBufferData = new WaveParticlesVertexData[nbParticles];

    float paddingx = 0.5f;
    float paddingz = 0.5f;

    for(int i = 0; i < areaWidth; ++i) {
        for(int j = 0; j < areaWidth; ++j) {
            float halfWidth = areaWidth / 4.0;

            float x = i * paddingx - halfWidth;
            float z = j * paddingz - halfWidth;

            waveBufferData[i*areaWidth + j].pos = Vec3(x, 0.0, z);
            waveBufferData[i*areaWidth + j].color = Vec3(1.0, 1.0, 1.0);
            waveBufferData[i*areaWidth + j].offset = Vec2(i, j);
        }
    }

    vector<VertexBufferDataInfo> dataInfos;

    GLsizei stride = sizeof(WaveParticlesVertexData);

    VertexBufferDataInfo colorInfo;
    colorInfo.attributeType = COLOUR_BUFFER;
    colorInfo.offset = sizeof(Vec3);
    colorInfo.dataType = GL_FLOAT;
    colorInfo.size = 3;

    dataInfos.push_back(colorInfo);

    VertexBufferDataInfo posInfo;
    posInfo.attributeType = VERTEX_BUFFER;
    posInfo.offset = 0;
    posInfo.dataType = GL_FLOAT;
    posInfo.size = 3;

    dataInfos.push_back(posInfo);

    VertexBufferDataInfo offsetInfo;
    offsetInfo.attributeType = OFFSET_BUFFER;
    offsetInfo.offset = 2 * sizeof(Vec3);
    offsetInfo.dataType = GL_FLOAT;
    offsetInfo.size = 2;

    dataInfos.push_back(offsetInfo);

    mesh->createInterleavedBufferData(dataInfos, waveBufferData,
                                      nbParticles * sizeof(WaveParticlesVertexData), GL_STATIC_DRAW, stride);

    delete[] waveBufferData;
}

void WaveParticlesNode::sendUniforms(Shader* material)
{
    material->sendUniform("width", areaWidth);
}

void WaveParticlesNode::preRender()
{
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(0.5);
}

void WaveParticlesNode::postRender()
{
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}
