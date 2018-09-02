#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Graphics/Buffers/IndexBuffer.hpp>

namespace Atom
{
	IndexBuffer::IndexBuffer(unsigned int* data, int count)
	{
		GLCall(glGenBuffers(1, &m_BufferID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_BufferID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}
