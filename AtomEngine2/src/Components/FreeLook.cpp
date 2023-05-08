#include "FreeLook.hpp"
#include <Core/GameObject.hpp>
#include <Input/Input.hpp>
#include <Time/Time.hpp>

namespace atom
{
    FreeLook::FreeLook(float rotFactor) : rotFactor(rotFactor)
    {
    }

    void FreeLook::Update()
	{
	    static bool lock = false;
        float rotAmt = rotFactor * Time::DeltaTime();

		if (Input::GetKeyUp(Key::TAB))
			Input::LockCursor(lock = !lock);

		Vector2 mouseMov = Input::GetMouseVel();

		parent->transform.Rotate(Vector3::UP, mouseMov.x * rotAmt);
		parent->transform.Rotate(parent->transform.rotation.GetRight(), mouseMov.y * rotAmt);
	}
}
