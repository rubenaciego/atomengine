#include "FreeMove.hpp"
#include <Core/GameObject.hpp>
#include <Input/Input.hpp>
#include <Time/Time.hpp>

namespace atom
{
    FreeMove::FreeMove(float movFactor) : movFactor(movFactor)
    {
    }

    void FreeMove::Update()
	{
        float movAmt = movFactor * Time::DeltaTime();

		if (Input::GetKey(Key::W))
			parent->transform.position += parent->transform.rotation.GetForward() * movAmt;
		if (Input::GetKey(Key::S))
			parent->transform.position += parent->transform.rotation.GetBack() * movAmt;
		if (Input::GetKey(Key::A))
			parent->transform.position += parent->transform.rotation.GetLeft() * movAmt;
		if (Input::GetKey(Key::D))
			parent->transform.position += parent->transform.rotation.GetRight() * movAmt;
	}
}
