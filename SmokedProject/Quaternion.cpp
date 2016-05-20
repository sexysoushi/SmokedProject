#include "Quaternion.h"

Quaternion::Quaternion()
    : w(0.0f),
      x(0.0f),
      y(0.0f),
      z(0.0f)
{

}


Quaternion::Quaternion(float w, float x, float y, float z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;

}

Quaternion Quaternion::operator*(const Quaternion& q){

    return Quaternion(
     w*q.w - x*q.x - y*q.y - z*q.z,
     w*q.x + x*q.w + y*q.z - z*q.y,
     w*q.y + y*q.w + z*q.x - x*q.z,
     w*q.z + z*q.w + x*q.y - y*q.x);

}


vec3 Quaternion::operator*(const vec3& v){

}

float Quaternion::operator*(float f){

}

Quaternion Quaternion::operator+(const Quaternion& q){
    return Quaternion(w+q.w, x+q.x, y+q.y, z+q.z);
}

Quaternion& Quaternion::operator*=(const Quaternion& q){

    float w_val = w*q.w - x*q.x - y*q.y - z*q.z;
    float x_val = w*q.x + x*q.w + y*q.z - z*q.y;
    float y_val = w*q.y + y*q.w + z*q.x - x*q.z;
    float z_val = w*q.z + z*q.w + x*q.y - y*q.x;

    w = w_val;
    x = x_val;
    y = y_val;
    z = z_val;

    return (*this);

}


float Quaternion::dot(const Quaternion& q){

}

void Quaternion::set(float x, float y, float z, float w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Quaternion::setFromAxis(float ax, float ay, float az, float aw){

}

Quaternion Quaternion::conjugate(){

}

Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t){

}

void Quaternion::normalize(){

}

void Quaternion::setRotationMatrix(float* mat){

}
