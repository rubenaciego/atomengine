#pragma once

#include <Math/Vector3.hpp>
#include <Components/GameComponent.hpp>
#include <Rendering/ShadowInfo.hpp>
#include <memory>

namespace atom
{
    class Shader;
    class Renderer3D;
    
    class BaseLight : public GameComponent
    {
    public:
        BaseLight(const Vector3& c = Vector3::ONE, float intens = 1);

        void AddToEngine(CoreEngine& engine);

        Vector3 color;
        float intensity;
        std::shared_ptr<Shader> shader;
        ShadowInfo shadowInfo;
    };
}
