#include "Material.hpp"
#include <ResourceManagement/TextureManager.hpp>
#include <Debug/Log.hpp>

namespace atom
{
    void Material::AddTexture(const std::string& name, const std::shared_ptr<Texture> tex)
    {
        textureMap[name] = tex;
    }

	void Material::AddVector3(const std::string& name, const Vector3& v)
    {
        vector3Map[name] = v;
    }

	void Material::AddFloat(const std::string& name, float val)
    {
        floatMap[name] = val;
    }

    const std::shared_ptr<Texture> Material::GetTexture(const std::string& name)
    {
        static unsigned char magenta[] = { 0xff, 0, 0xff, 0xff };
        static std::shared_ptr<Texture> magentaTex = TextureManager::CreateTexture(1, 1,
            magenta, "Magenta");
        static std::shared_ptr<Texture> normalDefault = TextureManager::CreateTexture("res/Textures/defaultNormal.jpg",
            "DefaultNormal");
        static std::shared_ptr<Texture> heightDefault = TextureManager::CreateTexture("res/Textures/defaultDisp.png",
            "DefaultHeight");
        
        try
        {
            return textureMap.at(name);
        }
        catch (const std::out_of_range& e)
        {
            if (name == "normal")
                return normalDefault;
            else if (name == "height")
                return heightDefault;
            else
            {
                ATOM_CORE_WARN("[Atom]: Warning, no material texture named %s\n", name.c_str());
                return magentaTex;
            }
        }
    }

	const Vector3& Material::GetVector3(const std::string& name)
    {
        try
        {
            return vector3Map.at(name);
        }
        catch (const std::exception& e)
        {
            ATOM_CORE_WARN("[Atom]: Warning, no material vector named %s\n", name.c_str());
            return Vector3::ZERO;
        }
    }

	float Material::GetFloat(const std::string& name)
    {
        try
        {
            return floatMap.at(name);
        }
        catch (const std::out_of_range& e)
        {
            ATOM_CORE_WARN("[Atom]: Warning, no material float named %s\n", name.c_str());
            return 0.0f;
        }
    }
}
