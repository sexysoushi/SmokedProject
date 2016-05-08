#ifndef MESH_H
#define MESH_H

#include <vector>

#include "shader.h"
#include "bufferattribute.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct VertexBufferDataInfo {
    BufferAttribute attributeType;
    int size;
    int offset;
    GLenum dataType;
};

class Mesh
{
private:
    Shader* material;
    GLuint vao;
    GLuint vbo;
    GLenum primitiveType;
    GLsizeiptr vertexDataSize;

public:
    Mesh(Shader* material, GLenum primitiveType);
    ~Mesh();

    Shader* getMaterial();
    void draw();
    void createInterleavedBufferData(const vector<VertexBufferDataInfo>& dataInfo,
                                     void* data, GLsizeiptr totalDataSize, GLenum usage, GLsizei stride);
};

#endif // MESH_H
