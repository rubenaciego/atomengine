#pragma once

#include <string>
#include <Rendering/OpenGL.hpp>

namespace atom
{
	enum TextureTarget : unsigned int
	{
		TEXTURE_2D = GL_TEXTURE_2D
	};

	enum TextureFilter : unsigned int
	{
		POINT_FILTER = GL_NEAREST,
		LINEAR_FILTER = GL_LINEAR,
		POINT_MIPMAP_POINT_FILTER = GL_NEAREST_MIPMAP_NEAREST,
		POINT_MIPMAP_LINEAR_FILTER = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_POINT_FILTER = GL_LINEAR_MIPMAP_NEAREST,
		LINEAR_MIPMAP_LINEAR_FILTER = GL_LINEAR_MIPMAP_LINEAR
	};

	enum TextureFormat : unsigned int
	{
		RGBA = GL_RGBA,
		RGB = GL_RGB,
		DEPTH16 = GL_DEPTH_COMPONENT16,
		DEPTH24 = GL_DEPTH_COMPONENT24,
		DEPTH = GL_DEPTH_COMPONENT
	};

	struct TextureParameters
	{
		static const TextureParameters DEFAULT;

		TextureTarget textureTarget;
		TextureFilter filter;
		TextureFormat internalFormat;
		TextureFormat format;
		unsigned int numTextures;
		bool clamp;
	};

	enum FrameBufferAttachments : unsigned int
	{
		NONE = GL_NONE,
		COLOR_BUFFER = GL_COLOR_ATTACHMENT0,
		DEPTH_BUFFER = GL_DEPTH_ATTACHMENT,
		STENCIL_BUFFER = GL_STENCIL_ATTACHMENT
	};

	class Texture
	{
	public:
		~Texture();

		void Bind(unsigned int textureUnit = 0);
		void BindAsRenderTarget();
		void InitFrameBuffer(FrameBufferAttachments attachments[]);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

	private:
		static Texture* lastBind;

		TextureParameters parameters;
		unsigned int* textureID;
		unsigned int frameBuffer;
		unsigned int renderBuffer;
		std::string name;
		unsigned int width;
		unsigned int height;

		Texture(const std::string& filename, const TextureParameters& params = TextureParameters::DEFAULT);
		Texture(int width, int height, unsigned char* data, const TextureParameters& params = TextureParameters::DEFAULT);

		void InitTextures(int width, int height, unsigned char* data, const TextureParameters& params);

		friend class Material;
		friend class TextureManager;
	};
}
