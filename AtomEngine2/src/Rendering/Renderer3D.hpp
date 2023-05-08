#pragma once

#include <Core/GameObject.hpp>
#include <Components/BaseLight.hpp>
#include <Components/Camera.hpp>
#include <list>
#include <unordered_map>
#include <memory>

namespace atom
{
    class Window;
    class Texture;
    
    class Renderer3D
    {
    private:
        Camera* camera;
        Window* window;
        Vector3 ambientLight;
        std::list<BaseLight*> lights;
        BaseLight* light;
        std::shared_ptr<Shader> forwardAmbient;
        std::shared_ptr<Shader> shadowShader;
        std::unordered_map<std::string, int> samplerMap;
        std::unordered_map<std::string, float> floatMap;
        std::unordered_map<std::string, Vector3> vectorMap;
        std::shared_ptr<Texture> shadowMap;
        Matrix4 lightMatrix;

    public:
        Renderer3D(Window* win);

        void Init();
        void Render(GameObject& gameObject);
        void AddLight(BaseLight* light);
        void AddCamera(Camera* cam);

        const Vector3& GetVector3(const std::string& name) const;
        float GetFloat(const std::string& name) const;
        int GetSamplerSlot(const std::string& name) const;
        const Matrix4& GetLightMatrix() const;
        BaseLight* GetLight();
        Camera* GetCamera();
    };
}
