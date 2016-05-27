#ifndef CAMERATEST_H
#define CAMERATEST_H
#include "src/Camera.h"
#include "src/glframe.h"
#include "src/particlesystem.h"
#include "src/Common/Shapes/Basis.h"
#include "src/Common/GlWindow.h"
#include <QSize>
#include <iostream>

class GlFrame: public GlWindow
{
    public:
        GlFrame(QWidget* parent=0);
        ~GlFrame();

        bool initializeObjects();

        void render();

        void mouseMoveEvent(QMouseEvent *);
        void keyPressEvent(QKeyEvent *);

        void addParticleSystem(ParticleSystem* ps);
        void clear();

    protected:
        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    private:
        std::vector<ParticleSystem*> p_systems;

};

#endif // CAMERATEST_H
