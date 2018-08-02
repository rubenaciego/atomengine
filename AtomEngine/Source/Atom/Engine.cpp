#include <FreeImage.h>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Audio/AudioManager.hpp>
#include <Atom/Graphics/Text/FontManager.hpp>
#include <Atom/Physics/Physics2D.hpp>
#include <Atom/Scenes/SceneManager.hpp>
#include <Atom/Graphics/Window.hpp>
#include <Atom/Time/Time.hpp>
#include <Atom/Math/Math.hpp>
#include <Atom/Engine.hpp>

namespace atom
{
	Window* Engine::m_Window = nullptr;

	void Engine::Init(const std::string& windowTitle, int width, int height)
	{	
		Debug::Log("Initializing engine...\n");

		FontManager::Init();
		AudioManager::Init();
		Physics2DManager::Init();
		SceneManager::Init();
		Random::Init();

		m_Window = new Window(windowTitle, width, height);

		FreeImage_Initialise();

		Debug::Log("Engine initialized\n");
	}

	void Engine::Clean()
	{
		SceneManager::Clean();
		FontManager::Clean();
		AudioManager::Clean();
		Physics2DManager::Clean();

		FreeImage_DeInitialise();

		delete m_Window;

		Debug::Log("Engine cleaned\n");
	}

	void Engine::Update()
	{
		Time::m_DeltaTime = Time::m_Timer.Tick();

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
