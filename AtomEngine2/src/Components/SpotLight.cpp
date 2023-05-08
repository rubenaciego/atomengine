#include "SpotLight.hpp"
#include <ResourceManagement/ShaderManager.hpp>
#include <Debug/Log.hpp>

namespace atom
{
    SpotLight::SpotLight(const Vector3& color, float intens,
        const Vector3& atten, float cutoff) :
        PointLight(color, intens, atten), cutoff(cutoff)
    {
        shader = ShaderManager::CreateShader("ForwardSpot");
    }
}
