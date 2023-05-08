#include "PointLight.hpp"
#include <ResourceManagement/ShaderManager.hpp>
#include <cmath>

namespace atom
{
    PointLight::PointLight(const Vector3& color, float intens,
        const Vector3& atten) : BaseLight(color, intens), atten(atten)
    {
        shader = ShaderManager::CreateShader("ForwardPoint");
        
        float a = atten.z;
        float b = atten.y;
        float c = atten.x - COLOR_DEPTH * intensity * color.Max();

        range = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
    }
}
