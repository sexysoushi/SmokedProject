#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <assert.h>
#include <map>
#include "GL/glew.h"

#include "math/matrix3.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "bufferattribute.h"
#include "texture.h"

#define SHADER_PATH string("./shaders/")

using namespace std;

class Shader {
public:
    Shader(string shaderName);
    ~Shader(void);

    GLuint programId() const;
    void init(const map<string, BufferAttribute>& attributes);
    string getName() const;
    bool isInUse() const;
    void use() const;
    void release() const;

    void sendUniform(string name, float value) const;
    void sendUniform(string name, int value) const;
    void sendUniform(string name, const Matrix4& mat) const;
    void sendUniform(string name, const Matrix3& mat) const;
    void sendUniform(string name, const Vec2& vec) const;
    void sendUniform(string name, const Vec3& vec) const;
    void sendUniform(string name, const Vec4& vec) const;
    void sendUniform(string name, Texture* texture) const;

    void setAttribute(BufferAttribute attribute, const string& name);

private:
    void link();
    GLuint createShader(GLenum type, const string& file);
    void loadShaderSource(const string& file, string* into) const;
    void setDefaultAttributes(const map<string, BufferAttribute>& attributes);
    GLint uniform(string uniformName) const;

    GLuint fragment;
    GLuint vertex;
    GLuint program;
    bool linked;
    string name;
};


#endif // SHADER_H
