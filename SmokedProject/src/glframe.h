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
#include "Skybox.h"

using namespace std;

// typedef std::chrono::steady_clock Clock;

class GlFrame: public GlWindow
{
    public:
        GlFrame(QWidget* parent=0);
        ~GlFrame();

        bool initializeObjects();

        void render();

        void addParticleSystem(ParticleSystem* ps);
        void clear();

    protected:
        QSize sizeHint() const;
        QSize minimumSizeHint() const;

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *e);
        void mouseDoubleClickEvent(QMouseEvent *);
        void wheelEvent( QWheelEvent* );

    private:
        std::vector<ParticleSystem*> p_systems;  

        Basis* g_Basis;
        Camera* g_Camera;
        Skybox* g_Skybox;

        float timeSinceLastFrame;
        Clock::time_point currentTime;

        QPoint lastPos;

        float rotateSpeed;  // rad per ms
        float moveSpeed;    // units per ms

        float timeInterval(Clock::time_point start, Clock::time_point end){
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        void lookat();
        void rotateCamera(float angleY, float angleX);
        void translateCamera(float forward, float right);
};

#endif // CAMERATEST_H
