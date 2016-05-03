#include "camera.h"

Camera::Camera(Vec3 position,
               Quaternion orientation,
               float aspectRatio,
               float fovAngle,
               float nearPlane,
               float farPlane,
               ProjectionType type)
    : SceneNode(position, orientation)
{
	this->aspectRatio = aspectRatio;
	this->fovAngle = fovAngle;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
    this->projectionType = type;
}

Camera::~Camera()
{

}

Matrix4 Camera::getViewMatrix()
{
    buildViewMatrix();
	return this->viewMatrix;
}

Matrix4 Camera::getProjectionMatrix()
{
    buildProjectionMatrix();
	return this->projectionMatrix;
}

void Camera::setAspectRatio(float ratio)
{
    this->aspectRatio = ratio;
}

void Camera::setFOV(float angle)
{
    this->fovAngle = angle;
}

void Camera::setPlanes(float near, float far)
{
	this->nearPlane = near;
    this->farPlane = far;
}

Vec3 Camera::up() {
    Vec3 up = Matrix3::getInverse(getRotationMatrix()) * Vec3(0, 1, 0);
    return up;
}

Vec3 Camera::right() {
    Vec3 right = Matrix3::getInverse(getRotationMatrix()) * Vec3(1, 0, 0);
    return right;
}

Vec3 Camera::forward() {
    Vec3 forward = Matrix3::getInverse(getRotationMatrix()) * Vec3(0, 0, -1);
    return forward;
}

void Camera::buildViewMatrix()
{
    viewMatrix = Matrix4::createView(up(), right(), forward(),
                                     getTranslationMatrix().getTranslation() + getPosition());
}

void Camera::buildProjectionMatrix()
{
    switch(projectionType) {
        case Perspective: {
            float r, l, t, b, theta;
            theta = radians(fovAngle) / 2;
            r = nearPlane * tan(theta);
            l = -r;
            t = r * aspectRatio;
            b = -t;

            projectionMatrix = Matrix4::createPerspective(nearPlane, farPlane, r, l, t, b);
        }
        break;
        case Orthographic: {
            // orthographic does not work yet
            projectionMatrix = Matrix4::createOrthographic();
        }
    }
}
