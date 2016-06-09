#include "Texture.h"

Texture::Texture()
{
    //Coordonées de texture
    GLfloat tmpTexCoordinates[] = {1.0f, 0.0f,
                                0.0f, 0.0f,
                                0.0f, 1.0f,
                                1.0f, 1.0f};

    for(int i = 0 ; i < 4*2 ; i++)
            texCoordinates[i] = tmpTexCoordinates[i];

    // Chargement des textures
    const int NBR_TEXTURES = 2;
    GLuint texId[NBR_TEXTURES];
    glGenTextures( NBR_TEXTURES, texId );
    // Initialisation de la première texture stockée dans l'unité de texture #0
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texId[0] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture1_width, texture1_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tab_texture1 );
    // Initialisation de la seconde texture stockée dans l'unité de texture #1
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, texId[1] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture2_width, texture2_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tab_texture2 );

}

void Texture::initGLFrame()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tc = glGetAttribLocation(m_Framework->getCurrentShaderId(), "texCoord");
    glVertexAttribPointer(tc, 2, GL_FLOAT, GL_FALSE, 0, texCoordinates);
    glEnableVertexAttribArray(tc);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 imageWidth,
                 imageHeight,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image);
}


void Texture::closeGLFrame()
{
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(tc);
}
