#include <string>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/OpenGL.hpp>

namespace atom
{
	void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			Debug::Error("[OpenGL Error]: (" + std::to_string(error) + "): " + function +
				" " + file + ": " + std::to_string(line) + '\n');
			return false;
		}

		return true;
	}
}
