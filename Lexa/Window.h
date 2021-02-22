#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera.h"


namespace Lexa
{
	namespace Window
	{
		void Init(unsigned int width, unsigned int height);

		void Clear();

		void Refresh();

	}
}

