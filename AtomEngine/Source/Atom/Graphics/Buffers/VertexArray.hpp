#pragma once

#include <vector>

namespace atom
{
	class VertexBuffer;

	class VertexArray
	{
	private:
		unsigned int m_ArrayID;
		std::vector<VertexBuffer*> m_Buffers;
		
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(VertexBuffer* buffer, unsigned int index);
		void Bind() const;
		void Unbind() const;
	};
}
