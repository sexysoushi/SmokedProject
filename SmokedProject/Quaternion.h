#ifndef QUATERNION_H
#define QUATERNION_H
#include "Common/GlFramework.h"

class Quaternion
{
private:
    float w;
    float x;
    float y;
    float z;


public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);

    Quaternion operator*(const Quaternion& q);
    vec3 operator*(const vec3& v);
    float operator*(float f);
    Quaternion operator+(const Quaternion& q);
    Quaternion& operator*=(const Quaternion& q);
    float dot(const Quaternion& q);
    void set(float w, float x, float y, float z);
    void setFromAxis(float angle, float ax, float ay, float az);
    Quaternion conjugate();
    Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
    void normalize();
    void setRotationMatrix(float* mat);
};

#endif // QUATERNION_H
