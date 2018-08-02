#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef _DEBUG
	#include <Atom/Debug/Debug.hpp>

	#define GLCall(x) atom::GLClearError(); x; atom::Debug::Assert(atom::GLLogCall(#x, __FILE__, __LINE__))
#else
	#define GLCall(x) x
#endif

namespace atom
{
	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
}
