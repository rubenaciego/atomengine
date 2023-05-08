#pragma once

#include <Components/GameComponent.hpp>

namespace atom
{
    class FreeLook : public GameComponent
	{
	public:
		FreeLook(float rotFactor);

		void Update() override;

        float rotFactor;
	};
}
