#pragma once

#include <vector>
#include <Atom/Math/Math.hpp>
#include <Atom/Graphics/Color.hpp>

namespace atom
{
	class Texture;
	class Renderer2D;

	struct VertexData
	{
		Vector3 vertex;
		Vector2 texCoord;
		float texID;
		unsigned int color;
	};

	class Renderable2D
	{
	private:
		void SetTexCoordDefaults();

	protected:
		Vector3 m_Position;
		Vector2 m_Size;
		Vector3 m_Scale;
		float m_Angle;
		Color m_Color;
		std::vector<Vector2> m_TexCoord;
		Texture* m_Texture;

		Renderable2D();

	public:
		Renderable2D(Vector3 position, Vector2 size, Color color);
		virtual ~Renderable2D();
		
		const Vector3& GetPosition() const;
		const Vector2& GetSize() const;
		const Vector3& GetScale() const;
		const float GetAngle() const;
		const Color& GetColor() const;
		const std::vector<Vector2>& GetTexCoord() const;
		virtual const unsigned int GetTexID() const;

		virtual void Submit(Renderer2D* renderer) const;
		void SetColor(const Color& color);
		void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
		void SetColor(unsigned int color);
		void Rotate(float angle);
		void Move(const Vector3& movement);
		void Move(float x, float y, float z);
		void Move(const Vector2& movement);
		void Move(float x, float y);
		void SetAngle(float angle);
		void SetPosition(const Vector3& position);
		void SetPosition(const Vector2& position);
		void SetPosition(float x, float y, float z);
		void SetPosition(float x, float y);
		void SetScale(const Vector3& scale);
		void SetScale(const Vector2& scale);
		void SetScale(float x, float y, float z);
		void SetScale(float x, float y);
		void SetScale(float scale);
	};
}
