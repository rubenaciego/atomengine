#include "Renderer3D.hpp"
#include <Rendering/OpenGL.hpp>
#include <Rendering/Window.hpp>
#include <Rendering/Shader.hpp>
#include <ResourceManagement/TextureManager.hpp>
#include <ResourceManagement/ShaderManager.hpp>
#include <Debug/Log.hpp>

namespace atom
{
    Renderer3D::Renderer3D(Window* win) : window(win)
    {
        vectorMap["ambient"] = Vector3::ONE * 0.2f;
        samplerMap["diffuse"] = 0;
        samplerMap["normal"] = 1;
        samplerMap["height"] = 2;
        samplerMap["shadowMap"] = 3;
    }

    void Renderer3D::Init()
    {
        GLCall(glClearColor(0, 0, 0, 0));

        GLCall(glFrontFace(GL_CW));
        GLCall(glCullFace(GL_BACK));

        GLCall(glEnable(GL_CULL_FACE));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_DEPTH_CLAMP));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        forwardAmbient = ShaderManager::CreateShader("ForwardAmbient");
        shadowShader = ShaderManager::CreateShader("ShadowMap");

        TextureParameters params = { TextureTarget::TEXTURE_2D, TextureFilter::POINT_FILTER, TextureFormat::DEPTH16,
            TextureFormat::DEPTH, 1, true };
        FrameBufferAttachments att[] = { FrameBufferAttachments::DEPTH_BUFFER };

        shadowMap = TextureManager::CreateTexture(1024, 1024, nullptr, "shadowMap", params);
        shadowMap->InitFrameBuffer(att);

        ATOM_CORE_LOG("[Atom]: Rendering engine initialized\n");
        ATOM_CORE_LOG("[Atom]: Using OpenGL version %s\n", GLVersion());
        ATOM_CORE_LOG("[Atom]: Renderer device: %s\n", GLRenderer());
    }

    void Renderer3D::Render(GameObject& gameObject)
    {
        window->BindAsRenderTarget();
        ClearScreen();
        gameObject.Render(forwardAmbient, *this);

        for (BaseLight* baseLight : lights)
        {
            GLCall(glEnable(GL_BLEND));
            GLCall(glBlendFunc(GL_ONE, GL_ONE));
            GLCall(glDepthMask(false));
            GLCall(glDepthFunc(GL_EQUAL));

            light = baseLight;
            ShadowInfo& shadowInfo = light->shadowInfo;

            shadowMap->BindAsRenderTarget();
            GLCall(glClear(GL_DEPTH_BUFFER_BIT));

            if (shadowInfo.castShadows)
            {
                Matrix4 prevProj = camera->projection;
                Vector3 prevPos = camera->parent->transform.position;
                Quaternion prevRot = camera->parent->transform.rotation;

                camera->projection = shadowInfo.projection;
                camera->parent->transform.position = light->parent->transform.TransformedPos();
                camera->parent->transform.rotation = light->parent->transform.TransformedRot();
                lightMatrix = camera->GetViewProjection();

                gameObject.Render(shadowShader, *this);

                camera->projection = prevProj;
                camera->parent->transform.position = prevPos;
                camera->parent->transform.rotation = prevRot;
            }

            window->BindAsRenderTarget();
            gameObject.Render(light->shader, *this);

            GLCall(glDepthFunc(GL_LESS));
            GLCall(glDisable(GL_BLEND));
            GLCall(glDepthMask(true));
        }
    }

    void Renderer3D::AddLight(BaseLight* light)
    {    
        lights.push_back(light);
    }
    
    void Renderer3D::AddCamera(Camera* camera)
    {
        this->camera = camera;
    }

    Camera* Renderer3D::GetCamera()
    {
        return camera;
    }

    BaseLight* Renderer3D::GetLight()
    {
        return light;
    }

    const Matrix4& Renderer3D::GetLightMatrix() const
    {
        return lightMatrix;
    }

    const Vector3& Renderer3D::GetVector3(const std::string& name) const
    {
        return vectorMap.at(name);
    }

    float Renderer3D::GetFloat(const std::string& name) const
    {
        return floatMap.at(name);
    }

    int Renderer3D::GetSamplerSlot(const std::string& name) const
    {
        return samplerMap.at(name);
    }
}
