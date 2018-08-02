#include "MainScene.hpp"

MainScene::MainScene() : shader(new Shader("Shaders/StandardShader.vert",
	"Shaders/StandardShader.frag")), layer(shader)
{
	FontManager::Add(new Font("Fonts/Consolas.ttf", "Consolas", 50));
	AudioManager::Add(new Sound("MainTheme", "Sound/Menu.wav"));

	label = new Label("FPS: 0", -15.0f, 7.0f, Color(0, 255, 0, 255), "Consolas", 50);
	texture = new Texture("Resources/Mario.jpg");
	sp1 = new Mario(-10.0f, 0.0f, 5.0f, 5.0f, Color(0xFFFF00FF));
	sp2 = new Mario(10.0f, 0.0f, 3.0f, 3.0f, Color(0, 255, 0));

	layer.Add(sp1);
	layer.Add(sp2);
	layer.Add(label);

	AudioManager::Get("MainTheme")->Loop();
}

MainScene::~MainScene()
{
	delete texture;
}

void MainScene::Update()
{
	// shader->SetUniform2f("u_LightPos", Vector2(window.GetMouseX() * 32.0f / window.GetWidth() - 16.0f, 9.0f - window.GetMouseY() * 18.0f / window.GetHeight()));

	label->SetText("FPS: " + std::to_string((int)(1.0f / Time::DeltaTime())));

	if (Input::IsKeyTyped(KEY_P))
		AudioManager::Get("MainTheme")->Pause();
	if (Input::IsKeyTyped(KEY_C))
		AudioManager::Get("MainTheme")->Resume();

	if (Input::IsKeyPressed(KEY_K))
		sp1->body.ApplyForce(Vector2(50, 0));
	if (Input::IsKeyPressed(KEY_H))
		sp1->body.ApplyForce(Vector2(-50, 0));
	if (Input::IsKeyPressed(KEY_U))
		sp1->body.ApplyForce(Vector2(0, 500));

	if (Input::IsKeyPressed(KEY_D))
		sp2->body.ApplyForce(Vector2(50, 0));
	if (Input::IsKeyPressed(KEY_A))
		sp2->body.ApplyForce(Vector2(-50, 0));
	if (Input::IsKeyPressed(KEY_W))
		sp2->body.ApplyForce(Vector2(0, 500));

	sp1->SetPosition(sp1->body.GetPos());
	sp2->SetPosition(sp2->body.GetPos());

	sp1->SetAngle(-Math::ToDegrees(sp1->body.GetAngle()));
	sp2->SetAngle(-Math::ToDegrees(sp2->body.GetAngle()));
}

void MainScene::Render()
{
	layer.Render();
}
