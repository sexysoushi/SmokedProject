#ifndef CUBMAPTEXTURE_H
#define CUBMAPTEXTURE_H
#include "Common/GlFramework.h"

using namespace std;

class CubmapTexture
{
public:

    CubmapTexture(const string& Directory,
        const string& PosXFilename,
        const string& NegXFilename,
        const string& PosYFilename,
        const string& NegYFilename,
        const string& PosZFilename,
        const string& NegZFilename);

    ~CubmapTexture();

    bool Load();

    void Bind(GLenum TextureUnit);

private:

    string m_fileNames[6];
    GLuint m_textureObj;
};

#endif // CUBMAPTEXTURE_H
