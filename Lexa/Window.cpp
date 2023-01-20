#include <glad/glad.h>

#include "Window.h"
#include "EventHandler.hpp"


namespace Lexa
{
	Window::Window(int width, int height) : 
		m_window(nullptr, [](GLFWwindow* ptr) {glfwDestroyWindow(ptr); }),
		m_width(width),
		m_height(height)
	{
		m_window.reset((glfwCreateWindow(width, height, "Lexa", nullptr, nullptr)));

		if (!glfwGetCurrentContext())
		{
			MakeCurrent();
		}
	}


	void Window::MakeCurrent()
	{
		glfwMakeContextCurrent(m_window.get());
	}


	int Window::GetWidth() const
	{
		return m_width;
	}


	int Window::GetHeight() const
	{
		return m_height;
	}


	void Window::SetDimensions(int width, int height)
	{
		m_width = width;
		m_height = height;
	}


	void Window::Clear()
	{
		glClearColor(1.f, 0.75f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	Window::WindowPtr Window::Get()
	{
		return m_window.get();
	}
}
