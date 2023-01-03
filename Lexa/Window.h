#pragma once
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Lexa
{
	class Window
	{
	public:
		Window(int width, int height);

		void MakeCurrent();

		void Update();

		int GetWidth() const;

		int GetHeight() const;

	private:
		void UpdateWindowSize();

		void Clear();

		std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;

		int m_width;

		int m_height;
	};
}
