#include <locale>
#include <windows.h>
#include "Window.h"

namespace Lexa
{
	Window::Window(int width, int height) : m_window(nullptr, [](GLFWwindow* ptr) {glfwDestroyWindow(ptr); }),
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


	void Window::Update()
	{
		glfwSwapBuffers(m_window.get());
		glfwPollEvents();
		UpdateWindowSize();
		Clear();
	}


	int Window::GetWidth() const
	{
		return m_width;
	}


	int Window::GetHeight() const
	{
		return m_height;
	}


	void Window::UpdateWindowSize()
	{
		int width, height;
		glfwGetFramebufferSize(m_window.get(), &width, &height);
		m_width = width;
		m_height = height;
		glViewport(0, 0, m_width, m_height);
	}


	void Window::Clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
