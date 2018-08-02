#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Graphics/Buffers/VertexBuffer.hpp>

namespace atom
{
	VertexBuffer::VertexBuffer(float* data, int count, unsigned int componentCount)
	{
		m_ComponenetCount = componentCount;

		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
