#include <vector>
#include <cstdio>
#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Math/Math.hpp>
#include <Atom/Utils/FileUtils.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Shader.hpp>

namespace atom
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		m_ShaderID = glCreateProgram();
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string& vertexShader = ReadFile(vertexPath);
		std::string& fragmentShader = ReadFile(fragmentPath);

		const char* vSource = vertexShader.c_str();
		const char* fragSource = fragmentShader.c_str();

		glShaderSource(vertex, 1, &vSource, nullptr);
		glCompileShader(vertex);

		int result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &result);

			std::vector<char> error(result);
			glGetShaderInfoLog(vertex, result, &result, &error[0]);

			Debug::Error("Failed to compile the vertex shader: " + std::string(error.begin(), error.end()) + '\n');
			glDeleteShader(vertex);
		}

		glShaderSource(fragment, 1, &fragSource, nullptr);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &result);

			std::vector<char> error(result);
			glGetShaderInfoLog(fragment, result, &result, &error[0]);

			Debug::Error("Failed to compile the fragment shader: " + std::string(error.begin(), error.end()) + '\n');
			glDeleteShader(fragment);
		}

		glAttachShader(m_ShaderID, vertex);
		glAttachShader(m_ShaderID, fragment);

		glLinkProgram(m_ShaderID);
		glValidateProgram(m_ShaderID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		Debug::Log("Shader " + std::to_string(m_ShaderID) + " loaded\n");
	}

	Shader::~Shader()
	{
		Debug::Log("Deleted shader " + std::to_string(m_ShaderID) + "\n");
		glDeleteProgram(m_ShaderID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniformMat4f(const char* name, const Matrix4 &matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::SetUniform4f(const char* name, const Vector4 &vec)
	{
		glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::SetUniform2f(const char* name, const Vector2 &vec)
	{
		glUniform2f(GetUniformLocation(name), vec.x, vec.y);
	}

	void Shader::SetUniform3f(const char* name, const Vector3 &vec)
	{
		glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
	}

	void Shader::SetUniform3f(const char* name, const Vector4 &vec)
	{
		glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
	}

	void Shader::SetUniform1f(const char* name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const char* name, int count, float* values)
	{
		glUniform1fv(GetUniformLocation(name), count, values);
	}

	void Shader::SetUniform1iv(const char* name, int count, int* values)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void Shader::SetUniform1i(const char* name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	int Shader::GetUniformLocation(const char* name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int location = glGetUniformLocation(m_ShaderID, name);

		if (location == -1)
			Debug::Warning("Warning: uniform" + std::string(name) + "doesn't exist\n");

		m_uniformLocationCache[name] = location;
		return location;
	}
}
