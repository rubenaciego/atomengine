#include "TextureManager.hpp"
#include <Debug/Log.hpp>

namespace atom
{
    std::unordered_map<std::string, std::weak_ptr<Texture>> TextureManager::textures;

    std::shared_ptr<Texture> TextureManager::CreateTexture(const std::string& filename,
        const std::string& name, const TextureParameters& params)
    {
        const std::string& s = name.length() ? name : filename;

        try
        {
            std::shared_ptr<Texture> ptr = textures.at(s).lock();
            return ptr;
        }
        catch (const std::out_of_range& e)
        {
            std::shared_ptr<Texture> tex(new Texture(filename, params));
            textures[s] = tex;
            tex->name = s;

            return tex;
        }
    }

    std::shared_ptr<Texture> TextureManager::CreateTexture(int width, int height,
        unsigned char* data, const std::string& name, const TextureParameters& params)
    {
        try
        {
            std::shared_ptr<Texture> ptr = textures.at(name).lock();
            ATOM_CORE_WARN("[Atom]: Warning, atempting to creating existing texture: %s\n", name.c_str());
            return ptr;
        }
        catch (const std::out_of_range& e)
        {
            std::shared_ptr<Texture> tex(new Texture(width, height, data, params));
            textures[name] = tex;
            tex->name = name; 

            return tex;
        }
    }

    std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& name)
    {
        return textures.at(name).lock();
    }

    void TextureManager::Flush()
    {
        textures.clear();
    }

    void TextureManager::DeleteInstance(const std::string& name)
    {
        textures.erase(name);
    }
}
