#include <FreeImage.h>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Audio/AudioManager.hpp>
#include <Atom/Graphics/Text/FontManager.hpp>
#include <Atom/Physics/Physics2D.hpp>
#include <Atom/Scenes/SceneManager.hpp>
#include <Atom/Graphics/Window.hpp>
#include <Atom/Time/Time.hpp>
#include <Atom/Time/Timer.hpp>
#include <Atom/Math/Math.hpp>
#include <Atom/Engine.hpp>

namespace Atom
{
	namespace Time
	{
		extern Timer timer;
	}

	Window* Engine::m_Window = nullptr;

	void Engine::Init(const std::string& windowTitle, int width, int height)
	{	
		Debug::Log("[Atom]: Initializing engine...\n");

		FontManager::Init();
		AudioManager::Init();
		Physics2DManager::Init();
		Random::Init();

		m_Window = new Window(windowTitle, width, height);

		FreeImage_Initialise();

		Debug::Log("[Atom]: Engine initialized\n");
	}

	void Engine::Clean()
	{
		SceneManager::Clean();
		FontManager::Clean();
		AudioManager::Clean();
		Physics2DManager::Clean();

		FreeImage_DeInitialise();

		delete m_Window;

		Debug::Log("[Atom]: Engine cleaned\n");
	}

	void Engine::Update()
	{
		Time::deltaTime = Time::timer.Tick() * Time::timeScale;

		AudioManager::Update();
		SceneManager::Update();
		Physics2DManager::Update();
		m_Window->Update();
		m_Window->Clear();
		SceneManager::Render();
	}

	bool Engine::Running()
	{
		return !m_Window->Closed();
	}
}
