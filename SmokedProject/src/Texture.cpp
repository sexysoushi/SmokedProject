#include "Texture.h"

/*  This function loads a texture into an available gl buffer and
 *  returns the id of the said buffer to be passed to the shader
 *  for mapping.
 */

GLuint Texture::loadTexture(char *t)
{
    QImage im;
    if(!im.load(t))
    {
        qWarning("ERROR LOADING IMAGE");
    }
    im.load(t);

    QImage glImage = QGLWidget::convertToGLFormat( im );

    GLuint texId;

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    // no interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // no extension
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, glImage.width(), glImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glImage.bits() );


    return texId;
}
