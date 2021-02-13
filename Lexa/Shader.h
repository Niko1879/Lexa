#pragma once
#include <string>
#include "IO.h"
#include "glad/glad.h"


namespace Lexa
{
	namespace Shader
	{
		unsigned int CreateShader(const std::string& vertexSrc, const std::string& fragSrc);
	}
}