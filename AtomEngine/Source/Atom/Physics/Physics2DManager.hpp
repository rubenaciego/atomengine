#pragma once

class b2World;

namespace atom
{
	class Physics2DManager
	{
	private:
		Physics2DManager() {}
		static b2World* m_World;
	
	public:
		static void Init();
		static void Update();
		static void Clean();
	
		friend class Body2D;
	};
}
