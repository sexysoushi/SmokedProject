#ifndef CAMERA_H
#define CAMERA_H
#include "GlFramework.h"
#include "Quaternion.h"

class Camera
{

private:
    vec3 m_Position;
    Quaternion m_Orientation;
    GLMatrix m_ViewMAtrix;
    GLMatrix m_Projection;

public:
    Camera();

    void translate(float x, float y, float z);
    void translateX(float shift);
    void translateY(float shift);
    void translateZ(float shift);
    void rotate(float angle, float ax, float ay, float az);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    const GLMatrix& getViewMatrix();
    void setAspectRatio(float ar);
    void setPlanes(float np, float fp);
    void setFOV(float angle);
    const GLMatrix& getProjectionMatrix();

protected:
    void buildViexMatrix();
    void buildProjectionMatrix();
};

#endif // CAMERA_H
