#include <Atom.hpp>
#include "MainScene.hpp"

using namespace Atom;

int main(int argc, const char* argv[])
{
	Engine::Init("Atom Engine", 1024, 576);
	
	SceneManager::LoadScene<MainScene>();

	while (Engine::Running())
		Engine::Update();

	Engine::Clean();

	return 0;
}
