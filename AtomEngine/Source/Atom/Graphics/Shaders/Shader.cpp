#include <vector>
#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Math/Math.hpp>
#include <Atom/Utils/FileUtils.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Shaders/Shader.hpp>

namespace Atom
{
	Shader* Shader::StandardShader2D()
	{
		return new Shader(
			#include "StandardShader.vert"
			,
			#include "StandardShader.frag"
		);
	}

	Shader* Shader::ShadowShader2D()
	{
		return new Shader(
			#include "ShadowShader.vert"
			,
			#include "ShadowShader.frag"
		);
	}

	Shader::Shader(const char* vertexSource, const char* fragmentSource)
	{
		GLCall(m_ShaderID = glCreateProgram());
		GLCall(unsigned int vertex = glCreateShader(GL_VERTEX_SHADER));
		GLCall(unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER));

		GLCall(glShaderSource(vertex, 1, &vertexSource, nullptr));
		GLCall(glCompileShader(vertex));

		int result;
		GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));

		if (result == GL_FALSE)
		{
			GLCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &result));

			std::vector<char> error(result);
			GLCall(glGetShaderInfoLog(vertex, result, &result, &error[0]));

			Debug::Error("[OpenGL]: Failed to compile the vertex shader: " + std::string(error.begin(), error.end()) + '\n');
			GLCall(glDeleteShader(vertex));
		}

		GLCall(glShaderSource(fragment, 1, &fragmentSource, nullptr));
		GLCall(glCompileShader(fragment));
		GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));

		if (result == GL_FALSE)
		{
			GLCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &result));

			std::vector<char> error(result);
			GLCall(glGetShaderInfoLog(fragment, result, &result, &error[0]));

			Debug::Error("[OpenGL]: Failed to compile the fragment shader: " + std::string(error.begin(), error.end()) + '\n');
			GLCall(glDeleteShader(fragment));
		}

		GLCall(glAttachShader(m_ShaderID, vertex));
		GLCall(glAttachShader(m_ShaderID, fragment));

		GLCall(glLinkProgram(m_ShaderID));
		GLCall(glValidateProgram(m_ShaderID));

		GLCall(glDeleteShader(vertex));
		GLCall(glDeleteShader(fragment));

		Debug::Log("[Atom]: Shader " + std::to_string(m_ShaderID) + " loaded\n");
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_ShaderID));
		Debug::Log("[Atom]: Deleted shader " + std::to_string(m_ShaderID) + "\n");
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_ShaderID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void Shader::SetUniformMat4f(const char* name, const Matrix4 &matrix)
	{
		GLCall(glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name), 1, GL_FALSE, matrix.elements));
	}

	void Shader::SetUniform4f(const char* name, const Vector4 &vec)
	{
		GLCall((GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
	}

	void Shader::SetUniform2f(const char* name, const Vector2 &vec)
	{
		GLCall(glUniform2f(GetUniformLocation(name), vec.x, vec.y));
	}

	void Shader::SetUniform3f(const char* name, const Vector3 &vec)
	{
		GLCall(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
	}

	void Shader::SetUniform3f(const char* name, const Vector4 &vec)
	{
		GLCall(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
	}

	void Shader::SetUniform1f(const char* name, float value)
	{
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform1fv(const char* name, int count, float* values)
	{
		GLCall(glUniform1fv(GetUniformLocation(name), count, values));
	}

	void Shader::SetUniform1iv(const char* name, int count, int* values)
	{
		GLCall(glUniform1iv(GetUniformLocation(name), count, values));
	}

	void Shader::SetUniform1i(const char* name, int value)
	{
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}

	int Shader::GetUniformLocation(const char* name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		GLCall(int location = glGetUniformLocation(m_ShaderID, name));

		if (location == -1)
			Debug::Warning("[OpenGL]: Warning: uniform" + std::string(name) + "doesn't exist\n");

		m_uniformLocationCache[name] = location;
		return location;
	}
}
