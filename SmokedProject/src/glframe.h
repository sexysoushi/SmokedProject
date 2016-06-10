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

        // event handlers;
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *e);
        void mouseDoubleClickEvent(QMouseEvent *);
        void wheelEvent( QWheelEvent* );

    private:
        std::vector<ParticleSystem*> m_systems;

        // 3D objects
        Basis* m_Basis;
        Camera* m_Camera;
        Skybox* m_Skybox;

        // time handlers
        float m_timeSinceLastFrame;
        Clock::time_point m_currentTime;

        // mouse position
        QPoint m_lastPos;

        // speeds
        float m_rotateSpeed;  // rad per ms
        float m_moveSpeed;    // units per ms

        float timeInterval(Clock::time_point start, Clock::time_point end){
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        // camera operations
        void applyCameraTransformations();
        void rotateCamera(float angleY, float angleX);
        void translateCamera(float forward, float right);
};

#endif // CAMERATEST_H
