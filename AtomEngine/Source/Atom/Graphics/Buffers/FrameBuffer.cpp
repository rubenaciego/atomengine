#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Graphics/Buffers/FrameBuffer.hpp>

/* When using a this FrameBuffer people is
 * people is forced to use a texture but
 * there should be the option of RenderBuffer
 */

namespace Atom
{
	FrameBuffer::FrameBuffer(int width, int height)
	{
		GLCall(glGenFramebuffers(1, &m_BufferID));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));
		
		GLCall(glGenTextures(1, &m_TextureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	FrameBuffer::~FrameBuffer()
	{
		GLCall(glDeleteFramebuffers(1, &m_BufferID));
		GLCall(glDeleteTextures(1, &m_TextureID));
	}

	void FrameBuffer::Bind() const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));
	}

	void FrameBuffer::Unbind() const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	unsigned int FrameBuffer::GetTexID() const
	{
		return m_TextureID;
	}
}
