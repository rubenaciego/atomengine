#pragma once

#include <Components/PointLight.hpp>

namespace atom
{
    class SpotLight : public PointLight
    {
    public:
        SpotLight(const Vector3& color = Vector3::ONE, float intens = 1.0f,
            const Vector3& atten = Vector3::FORWARD, float cutoff = 0);

        Vector3 direction;
        float cutoff;
    };
}
