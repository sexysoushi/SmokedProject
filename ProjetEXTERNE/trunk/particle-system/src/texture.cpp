#include "texture.h"

Texture::Texture(const string& imagePath, const string& textureName, GLuint texIndex)
{
    loadImage(imagePath);
    format = GL_RGBA;
    type = GL_UNSIGNED_BYTE;
    internalFormat = GL_RGBA;
    textureIndex = texIndex;
    name = textureName;
}

void Texture::loadImage(const string& path)
{
    string completePath = DATA_PATH + path;
    image = QGLWidget::convertToGLFormat(QImage(QString(completePath.c_str())));
    width = image.width();
    height = image.height();
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}

GLuint Texture::bind()
{
    glActiveTexture(unitFromIndex(textureIndex));
    glBindTexture(GL_TEXTURE_2D, textureId);
    return textureId;
}

GLuint Texture::unitFromIndex(GLuint index)
{
    switch(index) {
        case 1: return GL_TEXTURE1;
        case 2: return GL_TEXTURE2;
        case 3: return GL_TEXTURE3;
        case 4: return GL_TEXTURE4;
        default: return GL_TEXTURE0;
    }
}

void Texture::unBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::init()
{
    glGenTextures(1, &textureId);

    bind();
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, image.bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unBind();
}

GLuint Texture::getTextureId() const
{
    return textureId;
}

GLuint Texture::getTextureIndex() const
{
    return textureIndex;
}

unsigned int Texture::getWidth() const
{
    return width;
}

unsigned int Texture::getHeight() const
{
    return height;
}

string Texture::getName() const
{
    return name;
}

void Texture::resize(int w, int h)
{
    width = w;
    height = h;

    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, NULL);
}

void Texture::setTextureIndex(GLuint index)
{
    textureIndex = index;
}

void Texture::setFiltering(GLint filtering)
{
    bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
    unBind();
}
