#include "QImageTest.h"

QImageTest::QImageTest(){
}
void QImageTest::drawShape(){
}

void QImageTest::loadGLTextures()
{
    if(!b.load("texture.png"))
    {
        //loads correctly
        qWarning("ERROR LOADING IMAGE");
    }

    b.load( "texture2.png" );
    t = QGLWidget::convertToGLFormat( b );

    //initialise la texture
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );

    //Dessine la texture
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void QImageTest::closeGLTextures()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
