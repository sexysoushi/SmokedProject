#include "Skybox.h"

Skybox::Skybox()
{
}

void Skybox::loadGLTextures()
{
    if(!b1.load("mossymountains_up.png"))
    {
        //loads correctly
        qWarning("ERROR LOADING IMAGE");
    }

    const int NBR_TEXTURES = 6;
    GLuint texId[NBR_TEXTURES];
    glGenTextures( NBR_TEXTURES, texId );

    //texture top
    b1.load( "mossymountains_up.png" );
    t_top = QGLWidget::convertToGLFormat( b1 );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t_top.width(), t_top.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t_top.bits() );

    //texture front
    b2.load( "mossymountains_front.png" );
    t_front = QGLWidget::convertToGLFormat( b2 );
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture(GL_TEXTURE_2D, texId[1]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t_front.width(), t_front.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t_front.bits() );

    //texture right
    b3.load( "mossymountains_right.png" );
    t_right = QGLWidget::convertToGLFormat( b3 );
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t_right.width(), t_right.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t_right.bits() );

    //texture left
    b4.load( "mossymountains_left.png" );
    t_left = QGLWidget::convertToGLFormat( b4 );
    glActiveTexture( GL_TEXTURE3 );
    glBindTexture(GL_TEXTURE_2D, texId[3]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t_left.width(), t_left.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t_left.bits() );

    //texture bottom
    b5.load( "mossymountains_down.png" );
    t_bottom = QGLWidget::convertToGLFormat( b5 );
    glActiveTexture( GL_TEXTURE4 );
    glBindTexture(GL_TEXTURE_2D, texId[4]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t_bottom.width(), t_bottom.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t_bottom.bits() );

    //texture back
    b6.load( "mossymountains_back.png" );
    t_back = QGLWidget::convertToGLFormat( b6 );
    glActiveTexture( GL_TEXTURE5 );
    glBindTexture(GL_TEXTURE_2D, texId[5]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t_back.width(), t_back.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t_back.bits() );

    //Dessine la texture
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glDisable(GL_TEXTURE_2D);


}

void Skybox::drawShape()
{
}

void
Skybox::drawSkybox()
{
    //chargement des textures
    loadGLTextures();


    if (m_Framework->useShader( "Skybox" ))
    {
        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        GLint t = glGetAttribLocation( m_Framework->getCurrentShaderId(), "tc" );
        glVertexAttribPointer( t, 2, GL_FLOAT, GL_FALSE, 0, texCoord );

        glBegin(GL_QUADS);
            // top
            //glColor3f(1.0f, 0.0f, 0.0f);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-50.0f, 50.0f, 50.0f);
            glTexCoord2f(0, 1);
            glVertex3f(50.0f, 50.0f, 50.0f);
            glTexCoord2f(0, 0);
            glVertex3f(50.0f, 50.0f, -50.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-50.0f, 50.0f, -50.0f);

            // front
            //glColor3f(0.0f, 0.0f, 0.0f);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(50.0f, -50.0f, 50.0f);
            glTexCoord2f(0, 1);
            glVertex3f(50.0f, 50.0f, 50.0f);
            glTexCoord2f(0, 0);
            glVertex3f(-50.0f, 50.0f, 50.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-50.0f, -50.0f, 50.0f);

            // right
            //glColor3f(0.0f, 0.0f, 1.0f);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(50.0f, 50.0f, -50.0f);
            glTexCoord2f(0, 1);
            glVertex3f(50.0f, 50.0f, 50.0f);
            glTexCoord2f(0, 0);
            glVertex3f(50.0f, -50.0f, 50.0f);
            glTexCoord2f(1, 0);
            glVertex3f(50.0f, -50.0f, -50.0f);

            // left
            //glColor3f(0.0f, 0.0f, 0.5f);
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-50.0f, -50.0f, 50.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-50.0f, 50.0f, 50.0f);
            glTexCoord2f(0, 0);
            glVertex3f(-50.0f, 50.0f, -50.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-50.0f, -50.0f, -50.0f);

            // bottom
            //glColor3f(0.5f, 0.0f, 0.0f);
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-50.0f, -50.0f, 50.0f);
            glTexCoord2f(0, 1);
            glVertex3f(50.0f, -50.0f, 50.0f);
            glTexCoord2f(0, 0);
            glVertex3f(50.0f, -50.0f, -50.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-50.0f, -50.0f, -50.0f);

            // back
            //glColor3f(0.0f, 0.5f, 0.0f);
            glNormal3f(0.0f, 0.0f, -1.0f);
            glTexCoord2f(1, 1);
            glVertex3f(50.0f, 50.0f, -50.0f);
            glTexCoord2f(0, 1);
            glVertex3f(50.0f, -50.0f, -50.0f);
            glTexCoord2f(0, 0);
            glVertex3f(-50.0f, -50.0f, -50.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-50.0f, 50.0f, -50.0f);
        glEnd();

        glDisableVertexAttribArray( t );
    }
}
