#include <Box2D.h>
#include <Atom/Time/Time.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Physics/Physics2DManager.hpp>

namespace atom
{
	b2World* Physics2DManager::m_World = nullptr;

	void Physics2DManager::Init()
	{
		m_World = new b2World(b2Vec2(0.0f, -10.0f));

		// Test
		b2BodyDef myBodyDef;
		b2EdgeShape polygonShape;
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0);
		polygonShape.Set(b2Vec2(-15, -5), b2Vec2(15, -5));
		m_World->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

		Debug::Log("Physics2D Manager initialized\n");
	}

	void Physics2DManager::Update()
	{
		m_World->Step(Time::DeltaTime(), 8, 3);
	}

	void Physics2DManager::Clean()
	{
		delete m_World;

		Debug::Log("Physics2D Manager cleaned\n");
	}
}
