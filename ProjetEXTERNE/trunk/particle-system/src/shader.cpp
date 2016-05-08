#include "shader.h"

Shader::Shader(string shaderName) : name(shaderName)
{
    linked = false;
}

void Shader::init(const map<string, BufferAttribute>& attributes) {
    program = glCreateProgram();

    string fragName = SHADER_PATH + name + string(".frag");
    string vertName = SHADER_PATH + name + string(".vert");

    try {
        vertex = createShader(GL_VERTEX_SHADER, vertName);
        fragment = createShader(GL_FRAGMENT_SHADER, fragName);
    } catch(exception& e) {
        cerr << e.what() << endl;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // must be done before linking
    setDefaultAttributes(attributes);

    link();
}

Shader::~Shader(void) {
    glDetachShader(program, fragment);
    glDeleteShader(fragment);

    glDetachShader(program, vertex);
    glDeleteShader(vertex);

    glDeleteProgram(program);
}

string Shader::getName() const {
    return name;
}

GLuint Shader::programId() const {
    return program;
}

void Shader::use() const {
    if(!isInUse())
        glUseProgram(programId());
}

void Shader::release() const {
    glUseProgram(0);
}

bool Shader::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (programId() == (GLuint)currentProgram);
}

void Shader::link() {
    glLinkProgram(program);

    GLint code;
    glGetProgramiv(program, GL_LINK_STATUS, &code);

    if(!code) {
        throw runtime_error("Link shader failure (" + name + ")");
    }
    linked = true;
}

void Shader::setAttribute(BufferAttribute attribute, const string &name) {
    if(!linked) {
        glBindAttribLocation(program, attribute, name.c_str());
    } else {
        throw logic_error("Trying to bind attribute after linking");
    }
}

void Shader::setDefaultAttributes(const map<string, BufferAttribute>& attributes) {
    map<string, BufferAttribute>::const_iterator it;
    for(it = attributes.begin(); it != attributes.end(); ++it) {
        glBindAttribLocation(program, it->second, it->first.c_str());
    }
}

void Shader::loadShaderSource(const string& path, string* into) const {
    ifstream file;
    string buffer;

    file.open(path.c_str());

    if(!file.is_open()) {
        throw runtime_error("Opening file failure" + path + " (" + name + ")");
    }

    while(!file.eof()) {
        getline(file, buffer);
        (*into) += buffer + "\n";
    }

    file.close();
}

GLuint Shader::createShader(GLenum type, const string& file) {
    string source;

    loadShaderSource(file, &source);

    GLuint shader = glCreateShader(type);

    const GLchar* chars = source.c_str();

    glShaderSource(shader, 1, &chars, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE) {
        char error[512];

        glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        cerr << "In shader: " << file << endl;
        cerr << error << endl;
        throw runtime_error("Can't compile shader " + file + " (" + name + ")");
    }

    return shader;
}

GLint Shader::uniform(string uniformName) const {
    GLint uniform = glGetUniformLocation(program, uniformName.c_str());

    //if(uniform < 0) {
    //    cerr << "uniform " << uniformName << " not found in shader " << getName() << endl;
    //    throw runtime_error("Uniform variable not found : " + uniformName + " (" + name + ")");
    //}

    return uniform;
}

void Shader::sendUniform(string name, const Matrix4& mat) const {
    assert(isInUse());
    glUniformMatrix4fv(uniform(name), 1, GL_FALSE, &mat.array[0]);
}

void Shader::sendUniform(string name, const Matrix3& mat) const {
    assert(isInUse());
    glUniformMatrix3fv(uniform(name), 1, GL_FALSE, &mat.array[0]);
}

void Shader::sendUniform(string name, float value) const {
    assert(isInUse());
    glUniform1f(uniform(name), value);
}

void Shader::sendUniform(string name, Texture* texture) const {
    assert(isInUse());
    glUniform1f(uniform(name), texture->getTextureIndex());
}

void Shader::sendUniform(string name, int value) const {
    assert(isInUse());
    glUniform1i(uniform(name), value);
}

void Shader::sendUniform(string name, const Vec2& vec) const {
    assert(isInUse());
    glUniform2f(uniform(name), vec.v[0], vec.v[1]);
}

void Shader::sendUniform(string name, const Vec3& vec) const {
    assert(isInUse());
    glUniform3f(uniform(name), vec.v[0], vec.v[1], vec.v[2]);
}

void Shader::sendUniform(string name, const Vec4& vec) const {
    assert(isInUse());
    glUniform4f(uniform(name), vec.v[0], vec.v[1], vec.v[2], vec.v[3]);
}
