#pragma once

#include <Atom/Audio/AudioManager.hpp>
#include <Atom/Audio/Sound.hpp>
#include <Atom/Time/Time.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Input/Input.hpp>
#include <Atom/Math/Math.hpp>
#include <Atom/Physics/Physics2D.hpp>
#include <Atom/Scenes/Scene.hpp>
#include <Atom/Scenes/SceneManager.hpp>
#include <Atom/Utils/FileUtils.hpp>
#include <Atom/Utils/StringUtils.hpp>
#include <Atom/Graphics/Layers/Layer.hpp>
#include <Atom/Graphics/Renderables/Sprite.hpp>
#include <Atom/Graphics/Text/Label.hpp>
#include <Atom/Graphics/Light2D.hpp>
#include <Atom/Graphics/Text/Font.hpp>
#include <Atom/Graphics/Text/FontManager.hpp>
#include <Atom/Graphics/Color.hpp>
#include <Atom/Graphics/Shaders/Shader.hpp>
#include <Atom/Graphics/Texture.hpp>
#include <Atom/Graphics/Window.hpp>
#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Types.hpp>
#include <Atom/Engine.hpp>

#if defined(_WIN32) && !defined(_DEBUG)
	#define main WinMain
#else
	#define main main
#endif
