#include <Atom/Graphics/Texture.hpp>
#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Graphics/Renderables/Renderable2D.hpp>

namespace Atom
{
	Renderable2D::Renderable2D() : m_Texture(nullptr), m_Color(0xffffffff)
	{
		SetTexCoordDefaults();
		m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	}

	Renderable2D::Renderable2D(Vector3 position, Vector2 size, Color color)
		: m_Position(position), m_Size(size), m_Color(color)
	{
		SetTexCoordDefaults();
		m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	}

	Renderable2D::~Renderable2D()
	{
	}

	void Renderable2D::SetTexCoordDefaults()
	{
		Vector2 vec;

		m_TexCoord.push_back(vec);
		vec.y = 1;
		m_TexCoord.push_back(vec);
		vec.x = 1;
		m_TexCoord.push_back(vec);
		vec.y = 0;
		m_TexCoord.push_back(vec);
	}

	void Renderable2D::Submit(Renderer2D* renderer) const
	{
		renderer->Sumbit(this);
	}

	const Vector3& Renderable2D::GetPosition() const
	{
		return m_Position;
	}
	
	const Vector2& Renderable2D::GetSize() const
	{
		return m_Size;
	}
	
	const Color& Renderable2D::GetColor() const 
	{
		return m_Color; 
	}

	const float Renderable2D::GetAngle() const
	{
		return m_Angle;
	}

	const Vector3& Renderable2D::GetScale() const
	{
		return m_Scale;
	}

	const std::vector<Vector2>& Renderable2D::GetTexCoord() const
	{
		return m_TexCoord;
	}

	const unsigned int Renderable2D::GetTexID() const 
	{
		return m_Texture ? m_Texture->GetID() : 0;
	}

	void Renderable2D::SetColor(const Color& color)
	{
		m_Color = color;
	}

	void Renderable2D::SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		m_Color.red = red;
		m_Color.green = green;
		m_Color.blue = blue;
		m_Color.alpha = alpha;
	}

	void Renderable2D::SetColor(unsigned int color)
	{
		m_Color.color = color;
	}

	void Renderable2D::Rotate(float angle)
	{
		m_Angle += angle;
	}

	void Renderable2D::Move(const Vector3& movement)
	{
		m_Position += movement;
	}

	void Renderable2D::Move(float x, float y, float z)
	{
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;
	}

	void Renderable2D::Move(const Vector2& movement)
	{
		m_Position.x += movement.x;
		m_Position.y += movement.y;
	}

	void Renderable2D::Move(float x, float y)
	{
		m_Position.x += x;
		m_Position.y += y;
	}

	void Renderable2D::SetAngle(float angle)
	{
		m_Angle = angle;
	}

	void Renderable2D::SetPosition(const Vector3& position)
	{
		m_Position = position;
	}

	void Renderable2D::SetPosition(const Vector2& position)
	{
		m_Position.x = position.x;
		m_Position.y = position.y;
		m_Position.z = 0.0f;
	}

	void Renderable2D::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}

	void Renderable2D::SetPosition(float x, float y)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = 0.0f;
	}

	void Renderable2D::SetScale(const Vector3& scale)
	{
		m_Scale = scale;
	}

	void Renderable2D::SetScale(const Vector2& scale)
	{
		m_Scale.x = scale.x;
		m_Scale.y = scale.y;
	}

	void Renderable2D::SetScale(float x, float y, float z)
	{
		m_Scale.x = x;
		m_Scale.y = y;
		m_Scale.z = z;
	}

	void Renderable2D::SetScale(float x, float y)
	{
		m_Scale.x = x;
		m_Scale.y = y;
	}

	void Renderable2D::SetScale(float scale)
	{
		m_Scale.x = scale;
		m_Scale.y = scale;
	}
}
