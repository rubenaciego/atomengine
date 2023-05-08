#pragma once

#include <Components/GameComponent.hpp>

namespace atom
{
    class FreeMove : public GameComponent
	{
	public:
		FreeMove(float rotFactor);

		void Update() override;

        float movFactor;
	};
}
