#pragma once

#include <Atom.hpp>

using namespace atom;

class TileLayer : public Layer
{
public:
	TileLayer(Shader* shader) : Layer(new Renderer2D(), shader,
		Matrix4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
	{
		int textures[16] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
		};

		shader->Bind();
		shader->SetUniform1iv("u_Textures", 16, textures);
	}

	~TileLayer() {}
};

class Mario : public Sprite
{
public:
	Body2D body;

	Mario(float x, float y, float width, float height, const Color &color) :
		Sprite(x, y, width, height, color), body(0, 0, Vector2(m_Size.x*m_Scale.x, m_Size.y*m_Scale.y)) {}
	Mario(float x, float y, float width, float height, Texture *texture) :
		Sprite(x, y, width, height, texture), body(0, 0, Vector2(m_Size.x*m_Scale.x, m_Size.y*m_Scale.y)) {}
};

class MainScene : Scene
{
public:
	MainScene();
	~MainScene();
	void Update() override;
	void Render() override;
	
private:
	Shader* shader;
	TileLayer layer;
	Label* label;
	Texture* texture;
	Mario* sp1;
	Mario* sp2;
};
