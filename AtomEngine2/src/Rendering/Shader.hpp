#pragma once

#include <Math/Vector3.hpp>
#include <Math/Matrix4.hpp>
#include <Rendering/Material.hpp>
#include <Core/Transform.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <list>

namespace atom
{
    class Renderer3D;
    class BaseLight;
    class DirectionalLight;
    class PointLight;
    class SpotLight;

    class Shader
    {
    public:
        virtual ~Shader();
        void Bind() const;

        void UpdateUniforms(Transform& transform, Material& material,
            Renderer3D& renderer3D);

        void SetUniform(const std::string& name, int value) const;
        void SetUniform(const std::string& name, float value) const;
        void SetUniform(const std::string& name, const Vector3& value) const;
        void SetUniform(const std::string& name, const Matrix4& value) const;
        void SetUniform(const std::string& name, const BaseLight& value) const;
        void SetUniform(const std::string& name, const DirectionalLight& value) const;
        void SetUniform(const std::string& name, const PointLight& value) const;
        void SetUniform(const std::string& name, const SpotLight& value) const;

    protected:
        int program;
        std::unordered_map<std::string, int> uniforms;
        std::list<std::pair<std::string, std::string>> uniformNames;
        std::vector<int> shaders;
        std::string name;

        Shader(const std::string& filename);

        void AddProgram(const std::string& text, int type);
        void AddUniform(const std::string& uniform);
        void AddUniformStructCheck(const std::string& name, const std::string& type,
            std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>>& data);
        void AddAllUniforms(const std::string& text);
        void FindUniformStructs(const std::string& text, std::unordered_map<std::string,
            std::list<std::pair<std::string, std::string>>>& data);
        std::shared_ptr<std::string> LoadShader(const std::string& fileName);
        void AddVertexShaderFromFile(const std::string& text);
        void AddGeometryShaderFromFile(const std::string& text);
        void AddFragmentShaderFromFile(const std::string& text);
        void AddVertexShader(const std::string& text);
        void AddGeometryShader(const std::string& text);
        void AddFragmentShader(const std::string& text);
        void CompileShader() const;

        friend class ShaderManager;
    };
}
