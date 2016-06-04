#ifndef CAMERA_H
#define CAMERA_H
#include "src/Common/GlFramework.h"
#include "Quaternion.h"

class Camera
{

private:
    Vec3 m_position;
    Quaternion m_Orientation;
    GLMatrix m_ViewMatrix;
    GLMatrix m_ProjectionMatrix;

    float _aspectRatio;
    float _nearPlane;
    float _farPlane;
    float _fieldOfView;

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

protected:
    void buildViewMatrix();
    void buildProjectionMatrix();
};

#endif // CAMERA_H
