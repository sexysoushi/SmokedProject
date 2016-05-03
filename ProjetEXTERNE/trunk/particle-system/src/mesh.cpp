#include "mesh.h"

Mesh::Mesh(Shader* material, GLenum primitiveType)
{
    this->material = material;
    this->vbo = 0;
    this->vao = 0;
    this->primitiveType = primitiveType;
    this->vertexDataSize = 0;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

Shader* Mesh::getMaterial()
{
    return material;
}

void Mesh::draw() {
    glBindVertexArray(vao);

    glDrawArrays(primitiveType, 0, vertexDataSize);

    glBindVertexArray(0);
}

void Mesh::createInterleavedBufferData(const vector<VertexBufferDataInfo>& dataInfo,
                                       void* data, GLsizeiptr totalDataSize, GLenum usage, GLsizei stride)
{
    this->vertexDataSize = totalDataSize;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, totalDataSize, data, usage);

    // send data
    vector<VertexBufferDataInfo>::const_iterator it;
    for(it = dataInfo.begin(); it != dataInfo.end(); ++it) {
        VertexBufferDataInfo info = (*it);
        glEnableVertexAttribArray(info.attributeType);
        glVertexAttribPointer(info.attributeType, info.size, info.dataType, GL_FALSE, stride, BUFFER_OFFSET(info.offset));
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
