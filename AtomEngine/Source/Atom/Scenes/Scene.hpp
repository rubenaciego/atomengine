#pragma once

namespace Atom
{
	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}
		virtual void Update() {}
		virtual void Render() {}
	};
}
