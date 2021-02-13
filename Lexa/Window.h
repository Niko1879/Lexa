#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Lexa
{
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height);
		~Window();

		void Clear();

		void Refresh();

	private:
		GLFWwindow* window;
	};
}

