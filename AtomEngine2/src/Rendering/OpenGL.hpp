#pragma once

#include <cassert>
#include <GL/glew.h>

#define GLCall(x) atom::GLClearError(); x; assert(atom::GLLogCall(#x, __FILE__, __LINE__))

namespace atom
{
    void SetTextures(bool enable);
    void UnbindTextures();
    void ClearScreen();
    void SetClearColor(float r, float g, float b, float a);
    const char* GLVersion();
    const char* GLRenderer();
    void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
}
