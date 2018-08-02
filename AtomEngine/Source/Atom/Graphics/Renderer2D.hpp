#pragma once

#include <vector>

namespace atom
{
	struct Matrix4;
	struct Vector3;
	struct Vector4;
	struct VertexData;
	struct FontData;
	struct Character;
	class Renderable2D;
	class IndexBuffer;
	class Shader;
	class Label;

	#define RENDERER2D_MAX_SPRITES 60000
	#define RENDERER2D_MAX_TEXTURES 16
	#define RENDERER2D_VERTEX_SIZE sizeof(VertexData)
	#define RENDERER2D_SPRITE_SIZE RENDERER2D_VERTEX_SIZE * 4
	#define RENDERER2D_BUFFER_SIZE RENDERER2D_SPRITE_SIZE * RENDERER2D_MAX_SPRITES
	#define RENDERER2D_INDICES_SIZE RENDERER2D_MAX_SPRITES * 6
	#define SHADER_VERTEX_INDEX 0
	#define SHADER_TEXCOORD_INDEX 1
	#define SHADER_TEXID_INDEX 2
	#define SHADER_COLOR_INDEX 3

	class Renderer2D
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		VertexData* m_Buffer;
		IndexBuffer* m_IBO;
		int m_IndexCount;
		Matrix4* m_TransformationBack;
		std::vector<Matrix4> m_TransformationStack;
		std::vector<unsigned int> m_TextureSlots;

	public:
		Renderer2D();
		~Renderer2D();

		void PushMatrix(const Matrix4 &matrix, bool override = false);
		void PopMatrix();
		void Begin();
		void End();
		void Sumbit(const Renderable2D* renderable);
		void Flush();
		void DrawString(const Label* label);
	};
}
