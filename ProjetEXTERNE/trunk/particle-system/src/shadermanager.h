#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>
#include <string>
#include <stdexcept>
#include "shader.h"
#include "bufferattribute.h"

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void init();
    void addShader(const string& shaderName);
    void addShader(Shader* shader);
    void addShader(Shader* shader, const string& name);
    Shader* getShader(const string& shaderName) const;
    map<string, BufferAttribute> getDefaultAttributes() const;

private:
    map<string, Shader*> shaders;
    map<string, BufferAttribute> defaultAttributes;
};

#endif // SHADERMANAGER_H
