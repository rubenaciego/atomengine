#include "Transform.hpp"
#include <Debug/Log.hpp>

namespace atom
{
	Transform::Transform(const Vector3& pos, const Quaternion& rot, const Vector3& scale) :
		position(pos), rotation(rot), scale(scale), parent(nullptr)
	{
	}

	void Transform::CalcTransformation()
	{
		Matrix4 translationMatrix;
		Matrix4 rotationMatrix = rotation.ToRotationMatrix();
		Matrix4 scaleMatrix;
		Matrix4 parentMatrix;

		if (parent != nullptr)
			parentMatrix = parent->transformation;

		translationMatrix.InitTranslation(position.x, position.y, position.z);
		scaleMatrix.InitScale(scale.x, scale.y, scale.z);

		transformation = parentMatrix * translationMatrix * rotationMatrix * scaleMatrix;
	}

	void Transform::Translate(const Vector3& v)
	{
		position += v;
	}

	void Transform::Rotate(const Vector3& axis, float angle)
	{
		rotation = Quaternion(axis, angle) * rotation;
		rotation.Normalize();
	}

	Vector3 Transform::TransformedPos() const
	{
		return parent->transformation.Transform(position);
	}

	Quaternion Transform::TransformedRot() const
	{
		Quaternion parentRot;

		if (parent != nullptr)
			parentRot = parent->TransformedRot();
		
		return parentRot * rotation;
	}
}
