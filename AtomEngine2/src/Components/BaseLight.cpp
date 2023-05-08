#include "BaseLight.hpp"
#include <Core/CoreEngine.hpp>

namespace atom
{
    BaseLight::BaseLight(const Vector3& c, float intens) : color(c),
        intensity(intens)
    {
        shadowInfo.castShadows = true;
        shadowInfo.projection.InitOrthographic(-40, 40, -40, 40, -40, 40);
    }

    void BaseLight::AddToEngine(CoreEngine& engine)
    {
        engine.GetRenderer3D().AddLight(this);
    }
}
