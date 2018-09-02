#include <cstddef>
#include <Atom/Graphics/OpenGL.hpp>
#include <freetype-gl.h>
#include <Atom/Graphics/Buffers/IndexBuffer.hpp>
#include <Atom/Graphics/Renderables/Renderable2D.hpp>
#include <Atom/Graphics/Text/Label.hpp>
#include <Atom/Graphics/Shaders/Shader.hpp>
#include <Atom/Graphics/Camera.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Engine.hpp>
#include <Atom/Graphics/Renderer2D.hpp>

namespace Atom
{
	Renderer2D::Renderer2D()
	{
		GLCall(glGenVertexArrays(1, &m_VAO));
		GLCall(glGenBuffers(1, &m_VBO));

		GLCall(glBindVertexArray(m_VAO));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, RENDERER2D_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW));

		GLCall(glEnableVertexAttribArray(SHADER_VERTEX_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_TEXID_INDEX));
		GLCall(glEnableVertexAttribArray(SHADER_COLOR_INDEX));

		GLCall(glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const void*)0));
		GLCall(glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const void*)offsetof(VertexData, VertexData::texCoord)));
		GLCall(glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const void*)offsetof(VertexData, VertexData::texID)));
		GLCall(glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER2D_VERTEX_SIZE, (const void*)offsetof(VertexData, VertexData::color)));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		unsigned int *indices = new unsigned int[RENDERER2D_INDICES_SIZE];

		for (int offset = 0, i = 0; i < RENDERER2D_INDICES_SIZE; i += 6)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, RENDERER2D_INDICES_SIZE);

		delete[] indices;
		GLCall(glBindVertexArray(0));

		m_TransformationStack.push_back(Matrix4::Identity());
		m_TransformationBack = &m_TransformationStack.back();
		m_IndexCount = 0;

		Debug::Log("[Atom]: Renderer2D initialized\n");
	}
	
	Renderer2D::~Renderer2D()
	{
		delete m_IBO;

		GLCall(glDeleteBuffers(1, &m_VBO));

		Debug::Log("[Atom]: Renderer2D destroyed\n");
	}

	void Renderer2D::PushMatrix(const Matrix4 &matrix, bool override)
	{
		if (override)
			m_TransformationStack.push_back(matrix);
		else
			m_TransformationStack.push_back(matrix * m_TransformationStack.back());

		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer2D::PopMatrix()
	{
		if (m_TransformationStack.size() > 1)
		{
			m_TransformationStack.pop_back();
			m_TransformationBack = &m_TransformationStack.back();
		}
	}

	void Renderer2D::Sumbit(const Renderable2D* renderable)
	{
		Vector2 size = renderable->GetSize();
		const Vector3& scale = renderable->GetScale();
		const std::vector<Vector2> &texCoord = renderable->GetTexCoord();
		const unsigned int texID = renderable->GetTexID();
		const unsigned int color = renderable->GetColor().color;
		const float angle = renderable->GetAngle();
		Vector3 pos = renderable->GetPosition() - Vector3(m_Camera->position.x, m_Camera->position.y, 0.0f);

		float texSlot = 0.0f;

		size.x *= scale.x;
		size.y *= scale.y;

		if (texID != 0)
		{
			bool found = false;

			for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == texID)
				{
					texSlot = i + 1.0f;
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_TextureSlots.size() >= RENDERER2D_MAX_TEXTURES)
				{
					End();
					Flush();
					Begin(m_Camera);
				}

				m_TextureSlots.push_back(texID);
				texSlot = (float)(m_TextureSlots.size());
			}
		}

		const Matrix4& rotation = *m_TransformationBack * Matrix4::Translation(pos) * Matrix4::Rotation(angle, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Translation(pos * -1.0f);

		pos.y -= size.y / 2;
		pos.x -= size.x / 2;

		m_Buffer->vertex = rotation * pos;
		m_Buffer->texID = texSlot;
		m_Buffer->texCoord = texCoord[0];																	
		m_Buffer->color = color;
		m_Buffer++;																							
																											
		pos.y += size.y;
		
		m_Buffer->vertex = rotation * pos;
		m_Buffer->texID = texSlot;																			
		m_Buffer->texCoord = texCoord[1];																	
		m_Buffer->color = color;
		m_Buffer++;																							
																											
		pos.x += size.x;																					
		
		m_Buffer->vertex = rotation * pos;
		m_Buffer->texID = texSlot;															
		m_Buffer->texCoord = texCoord[2];																	
		m_Buffer->color = color;
		m_Buffer++;																							
																											
		pos.y -= size.y;

		m_Buffer->vertex = rotation * pos;
		m_Buffer->texID = texSlot;
		m_Buffer->texCoord = texCoord[3];
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Renderer2D::Flush()
	{
		for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
		{
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
		}
		
		GLCall(glBindVertexArray(m_VAO));
		m_IBO->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr));

		m_IBO->Unbind();
		GLCall(glBindVertexArray(0));

		m_IndexCount = 0;
		m_TextureSlots.clear();
	}

	void Renderer2D::Begin(Camera* camera)
	{
		m_Camera = camera;
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void Renderer2D::End()
	{
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void Renderer2D::DrawString(const Label* label)
	{
		using namespace ftgl;

		const std::string& text = label->m_Text;
		const unsigned int color = label->GetColor().color;
		const unsigned int texID = label->m_Font->m_Atlas->id;
		const float angle = label->GetAngle();
		texture_font_t* font = label->m_Font->m_Font;
		Vector3 pos = label->m_Position;
		Vector3 newPos;
		Vector2 texCoords;
		bool found = false;
		float texSlot = 0.0f;

		for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == texID)
			{
				texSlot = i + 1.0f;
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_TextureSlots.size() >= RENDERER2D_MAX_TEXTURES)
			{
				End();
				Flush();
				Begin(m_Camera);
			}

			m_TextureSlots.push_back(texID);
			texSlot = (float)(m_TextureSlots.size());
		}

		/*
		 *	TO DO: Set the scale correctly
		 */

		const float scaleX = Engine::m_Window->GetWidth() / 32.0f;
		const float scaleY = Engine::m_Window->GetHeight() / 18.0f;

		const Matrix4& rotation = *m_TransformationBack * Matrix4::Translation(pos) * Matrix4::Rotation(angle, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Translation(pos * -1.0f);

		for (unsigned int i = 0; i < text.length(); i++)
		{
			const char& c = text.at(i);
			const texture_glyph_t* glyph = texture_font_get_glyph(font, c);

			if (glyph != NULL)
			{
				if (i > 0)
					pos.x += texture_glyph_get_kerning(glyph, text.at(i - 1));

				const float x0 = pos.x + glyph->offset_x / scaleX;
				const float y0 = pos.y + glyph->offset_y / scaleY;
				const float x1 = x0 + (float)glyph->width / scaleX;
				const float y1 = y0 - (float)glyph->height / scaleY;

				const float v0 = glyph->t0;

				newPos.x = x0;
				newPos.y = y0;
				texCoords.x = glyph->s0;
				texCoords.y = v0;

				m_Buffer->vertex = rotation * newPos;
				m_Buffer->texID = texSlot;
				m_Buffer->color = color;
				m_Buffer->texCoord = texCoords;
				m_Buffer++;

				newPos.y = y1;
				texCoords.y = glyph->t1;

				m_Buffer->vertex = rotation * newPos;
				m_Buffer->texID = texSlot;
				m_Buffer->color = color;
				m_Buffer->texCoord = texCoords;
				m_Buffer++;

				newPos.x = x1;
				texCoords.x = glyph->s1;

				m_Buffer->vertex = rotation * newPos;
				m_Buffer->texID = texSlot;
				m_Buffer->color = color;
				m_Buffer->texCoord = texCoords;
				m_Buffer++;

				newPos.y = y0;
				texCoords.y = v0;

				m_Buffer->vertex = rotation * newPos;
				m_Buffer->texID = texSlot;
				m_Buffer->color = color;
				m_Buffer->texCoord = texCoords;
				m_Buffer++;

				m_IndexCount += 6;

				pos.x += glyph->advance_x / scaleX;
			}
		}
	}
}
