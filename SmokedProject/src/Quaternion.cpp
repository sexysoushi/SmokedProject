#include "Quaternion.h"

///////// PUBLIC //////////

/****** LIFE CYCLE *****/

Quaternion::~Quaternion(){}

Quaternion Quaternion::operator+(const Quaternion& q)
{
    Quaternion qres(this->w+q.w, this->x+q.x, this->y+q.y, this->z+q.z);
    return qres;
}

/***** Operators override *****/

// product with scalar
Quaternion Quaternion::operator*(float f)
{
    Quaternion q(f*w, f*x, f*y, f*z);
    return q;
}

// product with vector
Vec3 Quaternion::operator*(const Vec3& v)
{
    Quaternion u = Quaternion(0,v.x, v.y, v.z);
    Quaternion temp;
    Vec3 res;
    temp = (*this) * u * this->conjugate();
    res.x = temp.x;
    res.y = temp.y;
    res.z = temp.z;
    return res;
}

// products with quaternion

Quaternion Quaternion::operator*(const Quaternion& q)
{
    Quaternion qres = Quaternion();
    float qx = q.x;
    float qy = q.y;
    float qz = q.z;
    float qw = q.w;

    float qrx = w*qx + x*qw + y*qz - z*qy;
    float qry = w*qy - x*qz + y*qw + z*qx;
    float qrz = w*qz + x*qy - y*qx + z*qw;
    float qrw = w*qw - x*qx - y*qy - z*qz;

    qres.set(qrw, qrx, qry, qrz);
    //qres.normalize();
    return qres;
}

Quaternion& Quaternion::operator*=(const Quaternion& q)
{
    float qx = q.x;
    float qy = q.y;
    float qz = q.z;
    float qw = q.w;

    w = w*qw - x*qx - y*qy - z*qz;
    x = w*qx + x*qw + y*qz - z*qy;
    y = w*qy - x*qz + y*qw + z*qx;
    z = w*qz + x*qy - y*qx + z*qw;
    //this->normalize();
    return *this;
}


/************ SETTERS ***********/

void Quaternion::set(float qw, float qx, float qy, float qz)
{
    w=qw;
    x=qx;
    y=qy;
    z=qz;
}

///
/// \brief Quaternion::setFromAxis
///     Sets the quaternion from its rotation axis and angle
///     Axis should be normalized
/// \param angle
/// \param ax
/// \param ay
/// \param az
///
void Quaternion::setFromAxis(float angle, float ax, float ay, float az)
{
    w = cos(angle/2.0);
    x = ax*sin(angle/2.0);
    y = ay*sin(angle/2.0);
    z = az*sin(angle/2.0);
}

void Quaternion::setRotationMatrix(float* mat){
    mat[0] = 1.0f - 2.0f*y*y - 2.0f*z*z;
    mat[1] = 2.0f*x*y + 2.0f*w*z;
    mat[2] = 2.0f*x*z - 2.0f*w*y;
    mat[3] = 0.0f;
    mat[4] = 2.0f*x*y - 2.0f*w*z;
    mat[5] = 1.0f - 2.0f*x*x - 2.0f*z*z;
    mat[6] = 2.0f*y*z + 2.0f*w*x;
    mat[7] = 0.0f;
    mat[8] = 2.0f*x*z + 2.0f*w*y;
    mat[9] = 2.0f*y*z - 2.0f*w*x;
    mat[10] = 1.0f - 2.0f*x*x - 2.0f*y*y;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}


/********** OPERATIONS **********/

Quaternion Quaternion::conjugate()
{
    return Quaternion(w, -x, -y, -z);
}

void Quaternion::normalize()
{
    float magnitude = sqrt(w*w + x*x +y*y + z*z);
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

//float Quaternion::dot(const Quaternion& q) const
//{
//    float qx = q.x;
//    float qy = q.y;
//    float qz = q.z;
//    float qw = q.w;

//    return qx*x + qy*y + qz*z + qw*w;
//}

//Quaternion Quaternion::slerp(const Quaternion& q1,const Quaternion& q2,float t)
//{
//    Quaternion qr;
//    float dotproduct = q1.dot(q2);
//    float theta, st, sut, sout, coeff1, coeff2;

//    t=t/2.0;

//    theta = (float) acos(dotproduct);
//    if (theta<0.0) theta=-theta;

//    st = (float) sin(theta);
//    sut = (float) sin(t*theta);
//    sout = (float) sin((1-t)*theta);
//    coeff1 = sout/st;
//    coeff2 = sut/st;

//    qr.x = coeff1*q1.x + coeff2*q2.x;
//    qr.y = coeff1*q1.y + coeff2*q2.y;
//    qr.z = coeff1*q1.z + coeff2*q2.z;
//    qr.w = coeff1*q1.w + coeff2*q2.w;

//    qr.normalize();
//    return qr;
//}
