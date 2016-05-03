#ifndef CAMERA_H
#define CAMERA_H

#include "scenenode.h"
#include "math/matrix4.h"
#include "math/matrix3.h"

enum ProjectionType { Orthographic, Perspective };

class Camera : public SceneNode
{
    public:

        Camera(Vec3 position,
               Quaternion orientation,
               float aspectRatio,
               float fovAngle = 80.0f,
               float nearPlane = 0.01f,
               float farPlane = 1000.0f,
               ProjectionType type = Perspective);
        ~Camera();
        Matrix4 getViewMatrix();
        Matrix4 getProjectionMatrix();
        void setAspectRatio(float ratio);
        void setFOV(float angle);
        void setPlanes(float near, float far);
        Vec3 up();
        Vec3 right();
        Vec3 forward();

    protected:
        void buildViewMatrix();
        void buildProjectionMatrix();

    private:
        ProjectionType projectionType;
        Matrix4 viewMatrix, projectionMatrix;
        float aspectRatio, fovAngle, farPlane, nearPlane;
};

#endif // CAMERA_H
