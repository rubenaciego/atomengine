#pragma once

#include <string>

namespace atom
{
	class Texture
	{
	private:
		unsigned int m_TID;
		int m_Width;
		int m_Height;

	public:
		Texture(const std::string& path);
		~Texture();

		void Bind() const;
		void Unbind() const;

		inline const unsigned int GetWidth() const { return m_Width; }
		inline const unsigned int GetHeight() const { return m_Height; }
		inline const unsigned int GetID() const { return m_TID; }
	};
}
