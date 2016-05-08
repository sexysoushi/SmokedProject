#include "scenenode.h"

SceneNode::SceneNode()
{
    setScale(Vec3(1.0));
    updateTransform();
}

SceneNode::SceneNode(Vec3 position, Quaternion orientation) : position(position), orientation(orientation)
{
    setScale(Vec3(1.0));
    updateTransform();
}

SceneNode::~SceneNode()
{

}

Matrix4 SceneNode::getTransform() const
{
    return transform;
}

Vec3 SceneNode::getWorldPosition() const
{
    return transform * position;
}

void SceneNode::setPosition(const Vec3& position)
{
    this->position = position;
}

Vec3 SceneNode::getPosition() const
{
    return position;
}

void SceneNode::setScale(const Vec3& scale)
{
    this->scale = scale;
    updateTransform();
}

void SceneNode::rotate(float angle, const Vec3& axis) {
    Quaternion q(angle, axis);
    orientation = orientation * q;
    rotationMatrix = Matrix4::createRotation(orientation);
    updateTransform();
}

void SceneNode::rotateX(float angle) {
    Vec3 xAxis(1, 0, 0);
    rotate(angle, xAxis);
}

void SceneNode::rotateY(float angle) {
    Vec3 yAxis(0, 1, 0);
    rotate(angle, yAxis);
}

void SceneNode::rotateZ(float angle) {
    Vec3 zAxis(0, 0, 1);
    rotate(angle, zAxis);
}

void SceneNode::translate(const Vec3& translation) {
    Matrix4 t = Matrix4::createTranslation(translation);
    translationMatrix = translationMatrix * t;
    updateTransform();
}

void SceneNode::translateX(float value)
{
    translate(Vec3(value, 0.0, 0.0));
}

void SceneNode::translateY(float value)
{
    translate(Vec3(0.0, value, 0.0));
}

void SceneNode::translateZ(float value)
{
    translate(Vec3(0.0, 0.0, value));
}

void SceneNode::setOrientation(Quaternion orientation)
{
    this->orientation = orientation;
    updateTransform();
}

Quaternion SceneNode::getOrientation()
{
	return this->orientation;
}

void SceneNode::updateTransform()
{
    transform = getTranslationMatrix() * getRotationMatrix() * getScalingMatrix();
}

Matrix4 SceneNode::getRotationMatrix() const
{
    return rotationMatrix;
}

Matrix4 SceneNode::getTranslationMatrix() const
{
    return translationMatrix;
}

Matrix4 SceneNode::getScalingMatrix() const
{
    return Matrix4::createScale(scale);
}
