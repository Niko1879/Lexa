#include "Window.h"


namespace Lexa
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	Window::Window(unsigned int width, unsigned int height)
	{
		glfwInit();
		window = glfwCreateWindow(width, height, "Lexa", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glEnable(GL_DEPTH_TEST);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::Clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Refresh()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}