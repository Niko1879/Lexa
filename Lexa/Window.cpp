#include "Window.h"


namespace Lexa
{

	namespace Window
	{
		GLFWwindow* window;
		bool mouseDown = false;
		double cursorX, cursorY;

		void MouseHoldCallback()
		{
			double xNew, yNew;
			glfwGetCursorPos(window, &xNew, &yNew);
			Camera::OnDrag(xNew - cursorX, yNew - cursorY);
			cursorX = xNew;
			cursorY = yNew;
		}


		void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, 0.8*width, 0.8*height);
			Camera::OnWindowResize(width, height);
		}


		void ScrollCallback(GLFWwindow* window, double dx, double dy)
		{
			Camera::OnScroll(dy);
		}


		void MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
			{
				if (GLFW_PRESS == action)
				{
					glfwGetCursorPos(window, &cursorX, &cursorY);
					mouseDown = true;
				}

				else if (GLFW_RELEASE == action)
				{
					mouseDown = false;
				}
			}
		}


		void Init(unsigned int width, unsigned int height)
		{
			glfwInit();
			Camera::Init(width, height);
			window = glfwCreateWindow(width, height, "Lexa", NULL, NULL);
			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
			glfwSetScrollCallback(window, ScrollCallback);
			glfwSetMouseButtonCallback(window, MouseClickCallback);
			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			glEnable(GL_DEPTH_TEST);
		}


		void Clear()
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		void Refresh()
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
			if (mouseDown)
			{
				MouseHoldCallback();
			}
		}
	}
}