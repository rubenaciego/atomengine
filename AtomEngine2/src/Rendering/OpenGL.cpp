#include "OpenGL.hpp"
#include <Debug/Log.hpp>

namespace atom
{
	void SetTextures(bool enable)
    {
        if (enable)
        {
            GLCall(glEnable(GL_TEXTURE_2D));
        }
        else
        {
            GLCall(glDisable(GL_TEXTURE_2D));
        }
    }

    void UnbindTextures()
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void ClearScreen()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    }

    void SetClearColor(float r, float g, float b, float a)
    {
        GLCall(glClearColor(r, g, b, a));
    }
	
    const char* GLVersion()
    {
        return (char*)glGetString(GL_VERSION);
    }

    const char* GLRenderer()
    {
        return (char*)glGetString(GL_RENDERER);
    }

    void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			ATOM_CORE_ERROR("[Atom]: OpenGL error %i, %s %s line %i\n", error, function, file, line);
			return false;
		}

		return true;
	}
}
