#include "Shader.hpp"
#include <Debug/Log.hpp>
#include <Rendering/OpenGL.hpp>
#include <Components/BaseLight.hpp>
#include <Components/DirectionalLight.hpp>
#include <Components/SpotLight.hpp>
#include <Components/PointLight.hpp>
#include <Core/GameObject.hpp>
#include <Rendering/Renderer3D.hpp>
#include <Components/Camera.hpp>
#include <ResourceManagement/ShaderManager.hpp>
#include <ResourceManagement/TextureManager.hpp>
#include <cassert>
#include <memory>
#include <fstream>

namespace atom
{
    static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);

    Shader::Shader(const std::string& filename)
    {
        GLCall(program = glCreateProgram());

        if (program == 0)
            ATOM_CORE_ERROR("[Atom]: Error creating shader program\n");

        const std::shared_ptr<std::string> vtext = LoadShader(filename + ".vs");
		const std::shared_ptr<std::string> ftext = LoadShader(filename + ".fs");

		AddVertexShader(*vtext);
		AddFragmentShader(*ftext);
		CompileShader();

		AddAllUniforms(*vtext);
		AddAllUniforms(*ftext);
    }

    Shader::~Shader()
    {
        for (std::vector<int>::iterator it = shaders.begin(); it != shaders.end(); ++it) 
        {
            GLCall(glDetachShader(program, *it));
            GLCall(glDeleteShader(*it));
        }

        GLCall(glDeleteProgram(program));

        ShaderManager::DeleteInstance(name);
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(program));
    }

    void Shader::UpdateUniforms(Transform& transform, Material& material,
            Renderer3D& renderer3D)
    {
        Camera* camera = renderer3D.GetCamera();

        Matrix4& worldMatrix = transform.transformation;
		Matrix4 mvpMatrix = camera->GetViewProjection() * worldMatrix;

        for (auto& i : uniformNames)
        {
            std::string& name = i.second;
            std::string& type = i.first;

            if (type.compare("sampler2D") == 0)
            {
                int samplerSlot = renderer3D.GetSamplerSlot(name);

                if (name.compare("shadowMap") == 0)
                    TextureManager::GetTexture(name)->Bind(samplerSlot);
                else
                    material.GetTexture(name)->Bind(samplerSlot);

                SetUniform(name, samplerSlot);
            }
            else if (name.rfind("T_", 0) == 0)
            {
                if (name.compare("T_mvp") == 0)
                    SetUniform(name, mvpMatrix);
                else if (name.compare("T_world") == 0)
                    SetUniform(name, worldMatrix);
                else
                    ATOM_CORE_ERROR("[Atom]: Error, unknown uniform named %s %s\n", type.c_str(), name.c_str());
            }
            else if (name.rfind("R_", 0) == 0)
            {
                std::string unprefixedName = name.substr(2, name.length() - 2);

                if (unprefixedName.compare("lightingMatrix") == 0)
                    SetUniform(name, renderer3D.GetLightMatrix() * worldMatrix);
                else if (type.compare("vec3") == 0)
                    SetUniform(name, renderer3D.GetVector3(unprefixedName));
                else if (type.compare("float") == 0)
                    SetUniform(name, renderer3D.GetFloat(unprefixedName));
                else if (type.compare("DirectionalLight") == 0)
                    SetUniform(name, *(DirectionalLight*)renderer3D.GetLight());
                else if (type.compare("PointLight") == 0)
                    SetUniform(name, *(PointLight*)renderer3D.GetLight());
                else if (type.compare("SpotLight") == 0)
                    SetUniform(name, *(SpotLight*)renderer3D.GetLight());
            }
            else if (name.rfind("C_", 0) == 0)
            {
                if (name.compare("C_eyePos") == 0)
                    SetUniform(name, camera->parent->transform.TransformedPos());
            }
            else
            {
                if (type.compare("vec3") == 0)
                    SetUniform(name, material.GetVector3(name));
                else if (type.compare("float") == 0)
                    SetUniform(name, material.GetFloat(name));
            }
        }
    }

    void Shader::AddUniform(const std::string& uniform)
    {
        GLCall(int location = glGetUniformLocation(program, uniform.c_str()));

        if (location == -1)
            ATOM_CORE_WARN("[Atom]: Warning, uniform %s doesn't exist\n", uniform.c_str());

        uniforms.emplace(uniform, location);
    }

    void Shader::AddAllUniforms(const std::string& text)
    {
        static const std::string UNIFORM_KEYWORD = "uniform";

        std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>> structs;
		FindUniformStructs(text, structs);

        std::string::size_type uniformStartLoc = text.find(UNIFORM_KEYWORD, 0);

        while (uniformStartLoc != std::string::npos)
        {
            std::string::size_type begin = uniformStartLoc + UNIFORM_KEYWORD.length() + 1;
            std::string::size_type end = text.find(";", begin);

            std::string line = text.substr(begin, end - begin);
            
            std::string::size_type nameBegin = line.find(' ') + 1;
            std::string uniformName = line.substr(nameBegin, line.length() - nameBegin);
            std::string uniformType = line.substr(0, nameBegin - 1);

            uniformNames.push_back(std::make_pair(uniformType, uniformName));
            AddUniformStructCheck(uniformName, uniformType, structs);

            uniformStartLoc = text.find(UNIFORM_KEYWORD, uniformStartLoc + UNIFORM_KEYWORD.length());
        }
    }

    void Shader::AddUniformStructCheck(const std::string& name, const std::string& type,
            std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>>& data)
    {
        try
        {
            // If this throws an exception, that means it's not a struct type,
            // it's a native GLSL type
            auto structComponents = data.at(type);

            for (auto& i : structComponents)
                AddUniformStructCheck(name + "." + i.second, i.first, data);
        }
        catch (const std::out_of_range& e)
        {
            AddUniform(name);
        }
    }

    void Shader::FindUniformStructs(const std::string& text, std::unordered_map<std::string,
        std::list<std::pair<std::string, std::string>>>& data)
    {
        static const std::string STRUCT_KEYWORD = "struct";

        std::string::size_type structStartLoc = text.find(STRUCT_KEYWORD, 0);

        while (structStartLoc != std::string::npos)
        {
            std::string::size_type nameBegin = structStartLoc + STRUCT_KEYWORD.length() + 1;
            std::string::size_type braceBegin = text.find("{", nameBegin);
            std::string::size_type braceEnd = text.find("}", braceBegin);
            std::string structName = text.substr(nameBegin, braceBegin - 1 - nameBegin);

            // Now we get the member names of the struct
            std::list<std::pair<std::string, std::string>>& members = data[structName];
            std::string::size_type semicolonLoc = text.find(";", braceBegin);

            while (semicolonLoc != std::string::npos && semicolonLoc < braceEnd)
            {
                std::string::size_type nameStart = semicolonLoc;
                while (text[--nameStart] != ' ');
                nameStart++;

                std::string mem = text.substr(nameStart, semicolonLoc - nameStart);
                std::string::size_type typeEnd = nameStart - 1;
                std::string::size_type typeBegin = typeEnd;

                while (text[--typeBegin] != ' ');
                typeBegin++;

                std::string type = text.substr(typeBegin, typeEnd - typeBegin);
                
                members.push_back(std::make_pair(type, mem));
                semicolonLoc = text.find(";", semicolonLoc + 1);
            }

            structStartLoc = text.find(STRUCT_KEYWORD, structStartLoc + STRUCT_KEYWORD.length());
        }
    }

    void Shader::AddVertexShaderFromFile(const std::string& text)
    {
        AddVertexShader(*LoadShader(text));
    }

    void Shader::AddGeometryShaderFromFile(const std::string& text)
    {
        AddGeometryShader(*LoadShader(text));
    }

    void Shader::AddFragmentShaderFromFile(const std::string& text)
    {
        AddFragmentShader(*LoadShader(text));
    }

    void Shader::AddVertexShader(const std::string& text)
    {
        AddProgram(text, GL_VERTEX_SHADER);
    }

    void Shader::AddGeometryShader(const std::string& text)
    {
        AddProgram(text, GL_GEOMETRY_SHADER);
    }

    void Shader::AddFragmentShader(const std::string& text)
    {
        AddProgram(text, GL_FRAGMENT_SHADER);
    }

    void Shader::AddProgram(const std::string& text, int type)
    {
        GLCall(int shader = glCreateShader(type));

        if (shader == 0)
        {
            ATOM_CORE_ERROR("[Atom]: Error creating shader type %d\n", type);
            return;
        }

        const char* p[1];
        p[0] = text.c_str();
        int lengths[1];
        lengths[0] = text.length();

        GLCall(glShaderSource(shader, 1, p, lengths));
        GLCall(glCompileShader(shader));

        int success;
        GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

        if (!success) 
        {
            char InfoLog[1024];

            GLCall(glGetShaderInfoLog(shader, 1024, nullptr, InfoLog));
            ATOM_CORE_ERROR("[Atom]: Error compiling shader type %d: '%s'\n", shader, InfoLog);
            ATOM_CORE_LOG("%s\n", text.c_str());
        }

        GLCall(glAttachShader(program, shader));
        shaders.push_back(shader);
    }

    void Shader::CompileShader() const
    {
        GLCall(glLinkProgram(program));
        CheckShaderError(program, GL_LINK_STATUS, true, "Error linking shader program");

        GLCall(glValidateProgram(program));
        CheckShaderError(program, GL_VALIDATE_STATUS, true, "Invalid shader program");
    }

    void Shader::SetUniform(const std::string& name, int value) const
    {
        GLCall(glUniform1i(uniforms.at(name), value));
    }

    void Shader::SetUniform(const std::string& name, float value) const
    {
        GLCall(glUniform1f(uniforms.at(name), value));
    }

    void Shader::SetUniform(const std::string& name, const Vector3& value) const
    {
        GLCall(glUniform3f(uniforms.at(name), value.x, value.y, value.z));
    }

    void Shader::SetUniform(const std::string& name, const Matrix4& value) const
    {
        GLCall(glUniformMatrix4fv(uniforms.at(name), 1, GL_TRUE, &(value[0][0])));
    }

    void Shader::SetUniform(const std::string& name, const BaseLight& value) const
    {
		SetUniform(name + ".color", value.color);
		SetUniform(name + ".intensity", value.intensity);
    }

    void Shader::SetUniform(const std::string& name, const DirectionalLight& value) const
    {
        SetUniform(name + ".direction", value.parent->transform.TransformedRot().GetForward());
		SetUniform(name + ".base", (BaseLight)value);
    }

    void Shader::SetUniform(const std::string& name, const PointLight& value) const
    {
        SetUniform(name + ".base", (BaseLight)value);
		SetUniform(name + ".atten", value.atten);
		SetUniform(name + ".position", value.parent->transform.TransformedPos());
		SetUniform(name + ".range", value.range);
    }

    void Shader::SetUniform(const std::string& name, const SpotLight& value) const
    {
        SetUniform(name + ".pointLight", (PointLight)value);
		SetUniform(name + ".direction", value.parent->transform.TransformedRot().GetForward());
		SetUniform(name + ".cutoff", value.cutoff);
    }

    static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
    {
        int success = 0;
        char error[1024] = { 0 };

        if (isProgram)
        {
            GLCall(glGetProgramiv(shader, flag, &success));
        }
        else
        {
            GLCall(glGetShaderiv(shader, flag, &success));
        }

        if (!success)
        {
            if (isProgram)
            {
                GLCall(glGetProgramInfoLog(shader, sizeof(error), nullptr, error));
            }
            else
            {
                GLCall(glGetShaderInfoLog(shader, sizeof(error), nullptr, error));
            }

            ATOM_CORE_ERROR("[Atom]: %s: '%s'\n", errorMessage.c_str(), error);
        }
    }

    std::shared_ptr<std::string> Shader::LoadShader(const std::string& fileName)
    {
        static const std::string INCLUDE_DIR = "#include";

        std::ifstream file;
        file.open("./res/Shaders/" + fileName);

        std::shared_ptr<std::string> output(new std::string());
        std::string line;

        if (file.is_open())
        {
            while (file.good())
            {
                getline(file, line);

                if (line.rfind(INCLUDE_DIR, 0) == 0)
                {
                    int characters = INCLUDE_DIR.length() + 2;
                    auto str = LoadShader(line.substr(characters, line.length() - characters - 1));

                    output->append(str->c_str());
                }
                else
                    output->append(line + "\n");
            }
        }
        else
        {
            ATOM_CORE_ERROR("[Atom]: Unable to Load shader %s\n", fileName.c_str());
        }

        return output;
    };
}
