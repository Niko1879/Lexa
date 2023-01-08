#pragma once

#include <memory>

#include "GLFW/glfw3.h"


namespace Lexa
{
	class Window
	{
	public:
		Window(int width, int height);

		int GetWidth() const;

		int GetHeight() const;

		void SetDimensions(int width, int height);

		void Clear();

		void MakeCurrent();

	private:
		std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;
		int m_width;
		int m_height;
	};
}
