#pragma once

#include <Components/BaseLight.hpp>

namespace atom
{
    class DirectionalLight : public BaseLight
    {
    public:
        DirectionalLight(const Vector3& color = Vector3::ONE, float intens = 1.0f);
    };
}
