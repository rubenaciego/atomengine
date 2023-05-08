#include "DirectionalLight.hpp"
#include <ResourceManagement/ShaderManager.hpp>

namespace atom
{
    DirectionalLight::DirectionalLight(const Vector3& color, float intens) :
        BaseLight(color, intens)
    {
        shader = ShaderManager::CreateShader("ForwardDirectional");
    }
}
