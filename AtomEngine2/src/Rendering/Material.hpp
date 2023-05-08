#pragma once

#include <Rendering/Texture.hpp>
#include <Math/Vector3.hpp>
#include <unordered_map>
#include <memory>

namespace atom
{
	class Material
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> textureMap;
		std::unordered_map<std::string, Vector3> vector3Map;
		std::unordered_map<std::string, float> floatMap;

	public:
		void AddTexture(const std::string& name, const std::shared_ptr<Texture> tex);
		void AddVector3(const std::string& name, const Vector3& v);
		void AddFloat(const std::string& name, float val);

		const std::shared_ptr<Texture> GetTexture(const std::string& name);
		const Vector3& GetVector3(const std::string& name);
		float GetFloat(const std::string& name);
	};
}
