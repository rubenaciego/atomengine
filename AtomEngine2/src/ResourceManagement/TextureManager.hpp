#pragma once

#include <Rendering/Texture.hpp>
#include <unordered_map>
#include <memory>

namespace atom
{
    class TextureManager
    {
    public:
        static std::shared_ptr<Texture> CreateTexture(const std::string& filename,
            const std::string& name = "", const TextureParameters& params = TextureParameters::DEFAULT);
        static std::shared_ptr<Texture> CreateTexture(int width, int height,
            unsigned char* data, const std::string& name, const TextureParameters& params = TextureParameters::DEFAULT);
        
        static std::shared_ptr<Texture> GetTexture(const std::string& name);
        static void Flush();
        static void DeleteInstance(const std::string& name);
        
    private:
        TextureManager();
        
        static std::unordered_map<std::string, std::weak_ptr<Texture>> textures;
    };
}
