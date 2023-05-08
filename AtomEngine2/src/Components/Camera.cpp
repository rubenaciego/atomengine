#include "Camera.hpp"
#include <Time/Time.hpp>
#include <Input/Input.hpp>
#include <Core/CoreEngine.hpp>

namespace atom
{
	Camera::Camera(float fov, float aspect, float zNear, float zFar)
	{
		projection.InitPerspective(fov, aspect, zNear, zFar);
	}

	Camera::Camera(float left, float right, float bottom, float top, float near, float far)
	{
		projection.InitOrthographic(left, right, bottom, top, near, far);
	}
	
	void Camera::SetProjection(float fov, float aspect, float zNear, float zFar)
	{
		projection.InitPerspective(fov, aspect, zNear, zFar);
	}

	void Camera::SetProjection(float left, float right, float bottom, float top, float near, float far)
	{
		projection.InitOrthographic(left, right, bottom, top, near, far);
	}

	Matrix4 Camera::GetViewProjection() const
	{
		Matrix4 cameraRotation = parent->transform.TransformedRot().Conjugate().ToRotationMatrix();
		Matrix4 cameraTranslation;

		Vector3 cameraPos = parent->transform.TransformedPos();
		cameraTranslation.InitTranslation(-cameraPos.x, -cameraPos.y, -cameraPos.z);

		return projection * cameraRotation * cameraTranslation;
	}

	void Camera::AddToEngine(CoreEngine& engine)
	{
		engine.GetRenderer3D().AddCamera(this);
	}
}
