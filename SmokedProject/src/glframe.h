#ifndef CAMERATEST_H
#define CAMERATEST_H
#include "src/Camera.h"
#include "src/glframe.h"
#include "src/particlesystem.h"
#include "src/Common/Shapes/Basis.h"
#include "src/Common/GlWindow.h"
#include <QSize>
#include <iostream>
#include <chrono>

using namespace std;

// typedef std::chrono::steady_clock Clock;

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

        GLfloat angle1 = 0.0f;
        GLfloat angle2 = 0.0f;

        Basis* g_Basis;
        Camera* g_Camera;

//        float timeSinceLastFrame;
//        Clock::time_point currentTime;

        float oldMouseX;
        float oldMouseY;


//        float timeInterval(Clock::time_point start, Clock::time_point end){
//            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//        }
};

#endif // CAMERATEST_H
