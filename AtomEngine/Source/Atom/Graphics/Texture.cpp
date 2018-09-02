#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Utils/ImageUtils.hpp>
#include <Atom/Utils/StringUtils.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Texture.hpp>

namespace Atom
{
	Texture::Texture(const std::string& filename)
	{
		unsigned char* pixels = LoadImage(filename.c_str(), &m_Width, &m_Height);

		/* Texture arguments should be passed */

		GLCall(glGenTextures(1, &m_TID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TID));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0,
			GetExtension(filename) == "png" ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, pixels));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		delete[] pixels;

		Debug::Log("[Atom]: Texture " + filename + " loaded\n");
	}

	Texture::Texture(int width, int height, int texID)
	{
		m_Width = width;
		m_Height = height;
		m_TID = texID;
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_TID));
		Debug::Log("[Atom]: Deleted texture " + std::to_string(m_TID) + "\n");
	}

	void Texture::Bind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}
