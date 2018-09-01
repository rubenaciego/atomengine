#pragma once

#include <Atom.hpp>

using namespace Atom;

class Mario : public Sprite
{
public:
	Body2D body;

	Mario(float x, float y, float width, float height, const Color &color) :
		Sprite(x, y, width, height, color), body(0, 0, Vector2(m_Size.x*m_Scale.x, m_Size.y*m_Scale.y)) {}
	Mario(float x, float y, float width, float height, Texture *texture) :
		Sprite(x, y, width, height, texture), body(0, 0, Vector2(m_Size.x*m_Scale.x, m_Size.y*m_Scale.y)) {}
};

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();
	void Update() override;
	void Render() override;
	
private:
	Layer layer;
	Label* label;
	Texture* texture;
	Mario* sp1;
	Light2D light1;
	Light2D light2;
	Mario* sp2;
	Camera cam;
};
