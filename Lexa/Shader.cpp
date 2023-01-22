#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "Shader.h"


namespace Lexa
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragSrc) : m_id(nullptr, [](GLuint* ptr) { glDeleteProgram(*ptr); delete ptr; })
	{
		std::string vertexShaderCode = IO::ReadFile(vertexSrc);
		std::string fragmentShaderCode = IO::ReadFile(fragSrc);
		const char* vCode = vertexShaderCode.c_str();
		const char* fCode = fragmentShaderCode.c_str();

		std::unique_ptr<GLuint, void(*)(GLuint*)> vertexShader(new GLuint(glCreateShader(GL_VERTEX_SHADER)), [](GLuint* ptr) { glDeleteShader(*ptr); });
		glShaderSource(*vertexShader, 1, &vCode, NULL);
		glCompileShader(*vertexShader);
		int success;
		char infoLog[512];
		glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
		}

		std::unique_ptr<GLuint, void(*)(GLuint*)> fragmentShader(new GLuint(glCreateShader(GL_FRAGMENT_SHADER)), [](GLuint* ptr) { glDeleteShader(*ptr); });
		glShaderSource(*fragmentShader, 1, &fCode, NULL);
		glCompileShader(*fragmentShader);
		glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
		}

		m_id.reset(new GLuint(glCreateProgram()));
		glAttachShader(*m_id, *vertexShader);
		glAttachShader(*m_id, *fragmentShader);
		glLinkProgram(*m_id);
	}


	GLuint Shader::GetId() const
	{
		return m_id ? *m_id : 0;
	}


	void Shader::SetUniform3fv(const std::string& name, const glm::vec3& vec)
	{
		GLint id = GetUniformID(name.c_str());
		glUniform3fv(id, 1, glm::value_ptr(vec));
	}


	void Shader::SetUniform4fv(const std::string& name, const glm::vec4& vec)
	{
		GLint id = GetUniformID(name.c_str());
		glUniform4fv(id, 1, glm::value_ptr(vec));
	}


	void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat)
	{
		GLint id = GetUniformID(name.c_str());
		glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(mat));
	}


	GLint Shader::GetUniformID(const std::string& name) const
	{
		return glGetUniformLocation(*m_id, name.c_str());
	}


	void Shader::Bind() const
	{
		glUseProgram(*m_id);
	}
}