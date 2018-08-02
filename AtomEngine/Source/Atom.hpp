#pragma once

#include <Atom/Audio/Audio.hpp>
#include <Atom/Time/Time.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Input/Input.hpp>
#include <Atom/Math/Math.hpp>
#include <Atom/Physics/Physics2D.hpp>
#include <Atom/Scenes/Scenes.hpp>
#include <Atom/Utils/Utils.hpp>
#include <Atom/Graphics/Layers/Layers.hpp>
#include <Atom/Graphics/Renderables/Sprite.hpp>
#include <Atom/Graphics/Text/Text.hpp>
#include <Atom/Graphics/Color.hpp>
#include <Atom/Graphics/Shader.hpp>
#include <Atom/Graphics/Texture.hpp>
#include <Atom/Graphics/Window.hpp>
#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Engine.hpp>

#if defined(_WIN32) && !defined(_DEBUG)
	#define main WinMain
#else
	#define main main
#endif
