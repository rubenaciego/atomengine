#pragma once

#include <unordered_map>

#define ShaderFromFile(vertexPath, fragmentPath) Shader(ReadFile(vertexPath).c_str(), ReadFile(fragmentPath).c_str())


namespace Atom
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix4;

	class Shader
	{
	private:
		unsigned int m_ShaderID;
		std::unordered_map<const char*, int> m_uniformLocationCache;

		int GetUniformLocation(const char* name);
		
	public:
		Shader(const char* vertexSource, const char* fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniformMat4f(const char* name, const Matrix4 &matrix);
		void SetUniform4f(const char* name, const Vector4 &vec);
		void SetUniform2f(const char* name, const Vector2 &vec);
		void SetUniform3f(const char* name, const Vector3 &vec);
		void SetUniform3f(const char* name, const Vector4 &vec);
		void SetUniform1f(const char* name, float value);
		void SetUniform1fv(const char* name, int count, float* values);
		void SetUniform1iv(const char* name, int count, int* values);
		void SetUniform1i(const char* name, int value);
		
		static Shader* StandardShader2D();
		static Shader* ShadowShader2D();
		
	};
}
