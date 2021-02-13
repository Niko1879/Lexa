#include "Shader.h"
#include <iostream>

namespace Lexa
{
	namespace Shader
	{
		unsigned int CreateShader(const std::string& vertexSrc, const std::string& fragSrc)
		{
			std::string vertexShaderCode = IO::ReadFile(vertexSrc);
			std::string fragmentShaderCode = IO::ReadFile(fragSrc);
			const char* vCode = vertexShaderCode.c_str();
			const char* fCode = fragmentShaderCode.c_str();

			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vCode, NULL);
			glCompileShader(vertexShader);
			int success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fCode, NULL);
			glCompileShader(fragmentShader);
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			unsigned int shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return shaderProgram;
		}
	}
}