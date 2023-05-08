#pragma once

#include <Math/Vector3.hpp>
#include <Math/Matrix4.hpp>
#include <Components/GameComponent.hpp>

namespace atom
{
	class Camera : public GameComponent
	{
	public:
		Camera(float fov, float aspect, float zNear, float zFar);
		Camera(float left, float right, float bottom, float top, float near, float far);

		void SetProjection(float fov, float aspect, float zNear, float zFar);
		void SetProjection(float left, float right, float bottom, float top, float near, float far);
		Matrix4 GetViewProjection() const;
		void AddToEngine(CoreEngine& engine) override;

		Matrix4 projection;
	};
}
