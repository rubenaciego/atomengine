#pragma once

#include <Components/BaseLight.hpp>

namespace atom
{
    class PointLight : public BaseLight
    {
    private:
        const int COLOR_DEPTH = 256;

    public:
        PointLight(const Vector3& color = Vector3::ONE, float intens = 1.0f,
            const Vector3& atten = Vector3::FORWARD);

        Vector3 atten;
        float range;
    };
}
