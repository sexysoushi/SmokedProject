#ifndef SCENENODE_H
#define SCENENODE_H

#include "math/matrix4.h"

class SceneNode
{
	public:
		SceneNode();
        SceneNode(Vec3 position, Quaternion orientation);
        virtual ~SceneNode();

		// Orientation
		void setOrientation(Quaternion orientation);
		Quaternion getOrientation();

        void rotateX(float angle);
        void rotateY(float angle);
        void rotateZ(float angle);
        void translateX(float value);
        void translateY(float value);
        void translateZ(float value);
        void translate(const Vec3& translation);
        void rotate(float angle, const Vec3& axis);

        Matrix4 getTransform() const;
        Vec3 getWorldPosition() const;
        void setPosition(const Vec3& position);
        Vec3 getPosition() const;
        void setScale(const Vec3& scale);
        Vec3 getScale() const;

    protected:
        Matrix4 getScalingMatrix() const;
        Matrix4 getRotationMatrix() const;
        Matrix4 getTranslationMatrix() const;

     private:
        void updateTransform();
        Vec3 position;
        Vec3 scale;
        Quaternion orientation;

        Matrix4 transform;
        Matrix4 translationMatrix;
        Matrix4 rotationMatrix;

};

#endif // SCENENODE_H
