#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <glad\glad.h>
#include "GLFW/glfw3.h"

namespace Lexa
{
	namespace IO
	{
		std::string ReadFile(const std::string& filepath);
	}
}

