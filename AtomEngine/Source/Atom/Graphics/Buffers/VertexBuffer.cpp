#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Graphics/Buffers/VertexBuffer.hpp>

namespace Atom
{
	VertexBuffer::VertexBuffer(float* data, int count, unsigned int componentCount)
	{
		m_ComponenetCount = componentCount;

		GLCall(glGenBuffers(1, &m_BufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_BufferID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	unsigned int VertexBuffer::GetComponentCount() const
	{
		return m_ComponenetCount;
	}
}
