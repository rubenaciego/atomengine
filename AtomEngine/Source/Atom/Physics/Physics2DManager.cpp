#include <Box2D.h>
#include <Atom/Time/Time.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Physics/Physics2DManager.hpp>

namespace Atom
{
	namespace Physics2DManager
	{
		b2World* world = nullptr;

		void Init()
		{
			world = new b2World(b2Vec2(0.0f, -10.0f));

			// Test
			b2BodyDef myBodyDef;
			b2EdgeShape polygonShape;
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &polygonShape;
			myFixtureDef.density = 1;
			myBodyDef.type = b2_staticBody;
			myBodyDef.position.Set(0, 0);
			polygonShape.Set(b2Vec2(-15, -5), b2Vec2(15, -5));
			world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

			Debug::Log("[Atom]: Physics2D Manager initialized\n");
		}

		void Update()
		{
			world->Step(Time::deltaTime, 8, 3);
		}

		void Clean()
		{
			delete world;

			Debug::Log("[Atom]: Physics2D Manager cleaned\n");
		}
	}
}
