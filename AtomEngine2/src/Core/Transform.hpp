#pragma once

#include <Math/Matrix4.hpp>
#include <Math/Vector3.hpp>
#include <Math/Quaternion.hpp>

namespace atom
{
	class Camera;
	
	class Transform
	{
	public:
		Transform(const Vector3& pos = Vector3::ZERO, const Quaternion& rot = Quaternion(0, 0, 0, 1),
			const Vector3& scale = Vector3::ONE);

		void CalcTransformation();
		void Translate(const Vector3& v);
		void Rotate(const Vector3& axis, float angle);

		Vector3 TransformedPos() const;
		Quaternion TransformedRot() const;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		Transform* parent;
		Matrix4 transformation;
	};
}
