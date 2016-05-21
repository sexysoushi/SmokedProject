#ifndef CAMERATEST_H
#define CAMERATEST_H
#include "camera.h"

#include "GlWindow.h"

class Cameratest: public GlWindow
{
    public:
        Cameratest();
        ~Cameratest();

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
};

#endif // CAMERATEST_H
