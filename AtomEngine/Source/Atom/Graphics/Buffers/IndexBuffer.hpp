#pragma once

namespace Atom
{
	class IndexBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		IndexBuffer(unsigned int* data, int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}
