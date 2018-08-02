#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Utils/ImageUtils.hpp>
#include <Atom/Utils/StringUtils.hpp>
#include <Atom/Graphics/Texture.hpp>

namespace atom
{
	Texture::Texture(const std::string& filename)
	{
		unsigned char* pixels = LoadImage(filename.c_str(), &m_Width, &m_Height);

		/* Texture arguments should be passed */

		glGenTextures(1, &m_TID);
		glBindTexture(GL_TEXTURE_2D, m_TID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0,
			GetExtension(filename) == "png" ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] pixels;

		Debug::Log("Texture " + filename + " loaded\n");
	}

	Texture::~Texture()
	{
		Debug::Log("Deleted texture " + std::to_string(m_TID) + "\n");
		glDeleteTextures(1, &m_TID);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TID);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
