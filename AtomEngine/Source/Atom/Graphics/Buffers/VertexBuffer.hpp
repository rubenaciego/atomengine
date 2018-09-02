#pragma once

namespace Atom
{
	class VertexBuffer
	{
	private:
		unsigned int m_BufferID;
		unsigned int m_ComponenetCount;

	public:
		VertexBuffer(float* data, int count, unsigned int componentCount);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		unsigned int GetComponentCount() const;
	};
}
