#include <Atom.hpp>
#include "MainScene.hpp"

using namespace atom;

int main(int argc, const char* argv[])
{
	Engine::Init("Atom Engine", 1024, 576);
	
	SceneManager::Add<MainScene>("MainScene");
	SceneManager::LoadScene(0);

	while (Engine::Running())
		Engine::Update();

	Engine::Clean();

	return 0;
}

/*
	TODO:
		- 2D physics
		- improve API
		- some kind of multithreading
		- fix bugs (audio ?)
*/
