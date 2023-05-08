#include "Texture.hpp"
#include <ResourceManagement/TextureManager.hpp>
#include <Math/Math.hpp>
#include <Debug/Log.hpp>
#include <stb_image/stb_image.h>
#include <cstring>

namespace atom
{
	Texture* Texture::lastBind = nullptr;
	const TextureParameters TextureParameters::DEFAULT = { TextureTarget::TEXTURE_2D,
		TextureFilter::LINEAR_FILTER, TextureFormat::RGBA, TextureFormat::RGBA, 1, true };

	Texture::Texture(const std::string& filename, const TextureParameters& params)
	{
		int x, y, numComponents;
		unsigned char* data = stbi_load(filename.c_str(), &x, &y, &numComponents, 4);

		if (data == nullptr)
			ATOM_CORE_ERROR("[Atom]: Error, unable to load texture %s\n", filename.c_str());

		InitTextures(x, y, data, params);
		delete data;
	}

	Texture::Texture(int width, int height, unsigned char* data, const TextureParameters& params)
	{
		InitTextures(width, height, data, params);
	}

	void Texture::InitTextures(int width, int height, unsigned char* data, const TextureParameters& params)
	{
		parameters = params;
		this->width = width;
		this->height = height;
		frameBuffer = 0;
		textureID = new unsigned int[parameters.numTextures];
		TextureTarget textureTarget = parameters.textureTarget;
		
		if (width * height > 0)
		{
			GLCall(glGenTextures(parameters.numTextures, textureID));

			for (int i = 0; i < (int)parameters.numTextures; ++i)
			{
				GLCall(glBindTexture(textureTarget, textureID[i]));

				GLCall(glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, parameters.filter));
				GLCall(glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, parameters.filter));

				if (parameters.clamp)
				{
					GLCall(glTexParameterf(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
					GLCall(glTexParameterf(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
				}
				
				if (parameters.filter == TextureFilter::POINT_MIPMAP_POINT_FILTER ||
					parameters.filter == TextureFilter::POINT_MIPMAP_LINEAR_FILTER ||
					parameters.filter == TextureFilter::LINEAR_MIPMAP_POINT_FILTER ||
					parameters.filter == TextureFilter::LINEAR_MIPMAP_LINEAR_FILTER)
				{
					GLCall(glGenerateMipmap(textureTarget));
					float maxAnisotropy;
					GLCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy));
					GLCall(glTexParameterf(textureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, Clamp(0.0f, 8.0f, maxAnisotropy)));
				}
				else
				{
					GLCall(glTexParameteri(textureTarget, GL_TEXTURE_BASE_LEVEL, 0));
					GLCall(glTexParameteri(textureTarget, GL_TEXTURE_MAX_LEVEL, 0));
				}

				GLCall(glTexImage2D(textureTarget, 0, parameters.internalFormat,
					width, height, 0, parameters.format, GL_UNSIGNED_BYTE, data));
			}
		}
		else
		{
			memset(textureID, 0, parameters.numTextures * sizeof(textureID[0]));
		}
	}

	void Texture::InitFrameBuffer(FrameBufferAttachments attachments[])
	{
		if (attachments == nullptr)
			return;

		unsigned int drawBuffers[parameters.numTextures];
		bool hasDepth = false;

		for (int i = 0; i < (int)parameters.numTextures; ++i)
		{
			if (attachments[i] == FrameBufferAttachments::COLOR_BUFFER)
				drawBuffers[i] = attachments[i];
			else
			{
				if (attachments[i] == FrameBufferAttachments::DEPTH_BUFFER)
					hasDepth = true;
				
				drawBuffers[i] = FrameBufferAttachments::NONE;
			}
			
			if (attachments[i] == FrameBufferAttachments::NONE)
				continue;

			if (frameBuffer == 0)
			{
				GLCall(glCreateFramebuffers(1, &frameBuffer));
				GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer));
			}

			GLCall(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachments[i], parameters.textureTarget, textureID[i], 0));
		}

		if (frameBuffer == 0)
			return;

		if (!hasDepth)
		{
			GLCall(glCreateRenderbuffers(1, &renderBuffer));
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer));
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height));
			GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer));
		}
		
		GLCall(glDrawBuffers(parameters.numTextures, drawBuffers));
		GLCall(bool completed = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		
		if (!completed)
			ATOM_CORE_ERROR("[Atom]: FrameBuffer creation failed\n");
	}

	Texture::~Texture()
	{
		if (frameBuffer) { GLCall(glDeleteFramebuffers(1, &frameBuffer)); }
		if (renderBuffer) { GLCall(glDeleteRenderbuffers(1, &renderBuffer)); }
		if (textureID[0]) { GLCall(glDeleteTextures(parameters.numTextures, textureID)); }
		delete[] textureID;

		TextureManager::DeleteInstance(name);
	}

	void Texture::Bind(unsigned int textureUnit)
	{
		if (lastBind != this)
		{
			GLCall(glActiveTexture(GL_TEXTURE0 + textureUnit));
			GLCall(glBindTexture(parameters.textureTarget, textureID[0]));
			lastBind = this;
		}
	}

	void Texture::BindAsRenderTarget()
	{
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer));
		GLCall(glViewport(0, 0, width, height));
	}

	unsigned int Texture::GetWidth() const
	{
		return width;
	}

	unsigned int Texture::GetHeight() const
	{
		return height;
	}
}
