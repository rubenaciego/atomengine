#include <Box2D.h>
#include <Atom/Math/Math.hpp>
#include <Atom/Physics/Physics2D.hpp>
#include <Atom/Physics/Body2D.hpp>

namespace atom
{
	Body2D::Body2D(float x, float y, const Vector2& size, bool isStatic)
	{
		m_BodyDef = new b2BodyDef();
		m_BodyDef->type = isStatic ? b2_staticBody : b2_dynamicBody;
		m_BodyDef->position.Set(x, y);

		m_Body = Physics2DManager::m_World->CreateBody(m_BodyDef);
		m_Shape = new b2PolygonShape();
		m_Shape->SetAsBox(size.x / 2.0f - b2_polygonRadius, size.y / 2.0f - b2_polygonRadius);

		m_Fixture = new b2FixtureDef();
		m_Fixture->shape = m_Shape;

		if (isStatic)
		{
			m_Body->CreateFixture(m_Shape, 0);
		}
		else
		{
			m_Fixture->density = 0.3f;
			m_Fixture->friction = 0.1f;
			m_Fixture->restitution = 0.5f;
			m_Body->CreateFixture(m_Fixture);
		}
	}

	Body2D::~Body2D()
	{
		Physics2DManager::m_World->DestroyBody(m_Body);

		delete m_Shape;
		delete m_Fixture;
		delete m_BodyDef;
	}

	Vector2 Body2D::GetPos()
	{
		return Vector2(m_Body->GetPosition().x, m_Body->GetPosition().y);
	}

	float Body2D::GetAngle()
	{
		return m_Body->GetAngle();
	}

	void Body2D::ApplyForce(const Vector2& force)
	{
		m_Body->ApplyForce(b2Vec2(force.x, force.y), m_Body->GetWorldCenter(), true);
	}
}
