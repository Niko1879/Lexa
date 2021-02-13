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
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::Refresh()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}