#ifndef CAMERATEST_H
#define CAMERATEST_H
#include "Camera.h"
#include "glframe.h"
#include "particlesystem.h"
#include "Shapes/Basis.h"
#include "GlWindow.h"
#include <iostream>

class GlFrame: public GlWindow
{
    public:
        GlFrame(QWidget* parent=0);
        ~GlFrame();

        /*!
        *\brief Initialization des objets.
        */
        bool initializeObjects();

        /*!
        *\brief Rendu de la scène.
        */
        void render();

        void mouseMoveEvent(QMouseEvent *);
        void keyPressEvent(QKeyEvent *);

        ParticleSystem* getParticleSytem();

private:

        ParticleSystem* ps;

};

#endif // CAMERATEST_H
