#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Graphics/Buffers/VertexBuffer.hpp>
#include <Atom/Graphics/Buffers/VertexArray.hpp>

namespace atom
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray()
	{
		for (unsigned int i = 0; i < m_Buffers.size(); i++)
			delete m_Buffers[i];

		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::AddBuffer(VertexBuffer* buffer, unsigned int index)
	{
		Bind();
		buffer->Bind();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

		buffer->Unbind();
		Unbind();

		m_Buffers.push_back(buffer);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
}
