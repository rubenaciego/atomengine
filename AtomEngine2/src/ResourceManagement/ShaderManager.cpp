#include "ShaderManager.hpp"
#include <Rendering/Shader.hpp>
#include <Debug/Log.hpp>

namespace atom
{
    std::unordered_map<std::string, std::weak_ptr<Shader>> ShaderManager::shaders;

    std::shared_ptr<Shader> ShaderManager::CreateShader(const std::string& filename, const std::string& name)
    {
        const std::string& s = name.length() ? name : filename;

        try
        {
            std::shared_ptr<Shader> ptr = shaders.at(s).lock();
            return ptr;
        }
        catch (const std::out_of_range& e)
        {
            std::shared_ptr<Shader> shader(new Shader(filename));
            shaders[s] = shader;
            shader->name = s;

            return shader;
        }
    }

    std::shared_ptr<Shader> ShaderManager::GetShader(const std::string& name)
    {
        return shaders.at(name).lock();
    }

    void ShaderManager::Flush()
    {
        shaders.clear();
    }

    void ShaderManager::DeleteInstance(const std::string& name)
    {
        shaders.erase(name);
    }
}
