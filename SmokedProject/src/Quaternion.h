#ifndef QUATERNION_H
#define QUATERNION_H
#include <stdlib.h>
#include "src/Common/Vectors.h"
#include "src/Common/GlFramework.h"

// QUATERNION HANDLING TOOL CLASS
// Report to MathWorks -> Quaternions for details

class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;


public:
    Quaternion(): x(0), y(0), z(0), w(0) {}
    Quaternion(float ww, float xx, float yy, float zz): x(xx), y(yy), z(zz), w(ww) {}
    ~Quaternion();

    // operators override
    Vec3 operator*(const Vec3& v);
    Quaternion operator*(const Quaternion& q);
    Quaternion& operator*=(const Quaternion& q);
    Quaternion operator*(float f);
    Quaternion operator+(const Quaternion& q);

    // setters
    void set(float w, float x, float y, float z);
    void setFromAxis(float angle, float ax, float ay, float az);
    void setRotationMatrix(float* mat);

    // operations
    void normalize();

    Quaternion conjugate();

    //float dot(const Quaternion& q) const;
    //Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
};

#endif // QUATERNION_H
