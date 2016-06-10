#ifndef CAMERA_H
#define CAMERA_H
#include "src/Common/GlFramework.h"
#include "Quaternion.h"

// self explanatory camera handling class using quaternions

class Camera
{

private:
    Vec3 m_position;
    Quaternion m_Orientation;
    GLMatrix m_ViewMatrix;
    GLMatrix m_ProjectionMatrix;

    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
    float m_fieldOfView;

public:
    Camera();
    Camera(float posX, float posY, float posZ);
    Camera(float posX, float posY, float posZ, float ar, float np, float fp, float fov);
    ~Camera();

    void translate(float x, float y, float z);
    void translateX(float shift);
    void translateY(float shift);
    void translateZ(float shift);

    void rotate(float angle, float ax, float ay, float az);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void setAspectRatio(float ar);
    void setPlanes(float np, float fp);
    void setFOV(float angle);

    const GLMatrix& getViewMatrix();
    const GLMatrix& getProjectionMatrix();

    Quaternion getOrientation();
    Vec3 getPosition();

protected:
    void buildViewMatrix();
    void buildProjectionMatrix();
};

#endif // CAMERA_H
