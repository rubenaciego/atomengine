#pragma once

class b2Body;
class b2BodyDef;
class b2PolygonShape;
class b2FixtureDef;

namespace atom
{
	struct Vector2;

	class Body2D
	{
	protected:
		b2Body* m_Body;
		b2BodyDef* m_BodyDef;
		b2PolygonShape* m_Shape;
		b2FixtureDef* m_Fixture;
	
	public:
		Body2D(float x, float y, const Vector2& size, bool isStatic = false);
		~Body2D();
	
		Vector2 GetPos();
		float GetAngle();
		void ApplyForce(const Vector2& force);
	};
}
