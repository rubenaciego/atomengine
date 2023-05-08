#pragma once

#include <unordered_map>
#include <memory>

namespace atom
{
    class Shader;

    class ShaderManager
    {
    public:
        static std::shared_ptr<Shader> CreateShader(const std::string& filename, const std::string& name = "");
        
        static std::shared_ptr<Shader> GetShader(const std::string& name);
        static void Flush();
        static void DeleteInstance(const std::string& name);
        
    private:
        ShaderManager();
        
        static std::unordered_map<std::string, std::weak_ptr<Shader>> shaders;
    };
}
