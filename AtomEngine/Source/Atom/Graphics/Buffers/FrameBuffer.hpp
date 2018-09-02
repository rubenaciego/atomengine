#pragma once

namespace Atom
{
	class FrameBuffer
	{
	public:
		unsigned int m_BufferID;
		unsigned int m_TextureID;

	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();

		void Bind() const;
		void Unbind() const;
		unsigned int GetTexID() const;
	};
}
