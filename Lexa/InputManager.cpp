#include <GLFW/glfw3.h>

#include "InputManager.h"


namespace Lexa
{
	void GLFWScrollCallback(GLFWwindow* window, double dx, double dy)
	{
		InputManager::Data* p = (InputManager::Data*)(glfwGetWindowUserPointer(window));
		p->m_cursor.scrolldelta = dy;
	}


	void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			InputManager::Data* p = (InputManager::Data*)(glfwGetWindowUserPointer(window));
			p->m_text = "\b";
		}
	}


	void GLFWCharacterCallback(GLFWwindow* window, unsigned codepoint)
	{
		auto utf8convert = [](char32_t utf)
		{
			std::string ret;

			if (utf <= 0x7F) {
				// Plain ASCII
				ret = (char)utf;
			}
			else if (utf <= 0x07FF) {
				// 2-byte unicode
				ret = (char)(((utf >> 6) & 0x1F) | 0xC0);
				ret += (char)(((utf >> 0) & 0x3F) | 0x80);
			}
			else if (utf <= 0xFFFF) {
				// 3-byte unicode
				ret = (char)(((utf >> 12) & 0x0F) | 0xE0);
				ret += (char)(((utf >> 6) & 0x3F) | 0x80);
				ret += (char)(((utf >> 0) & 0x3F) | 0x80);
			}
			else if (utf <= 0x10FFFF) {
				// 4-byte unicode
				ret = (char)(((utf >> 18) & 0x07) | 0xF0);
				ret += (char)(((utf >> 12) & 0x3F) | 0x80);
				ret += (char)(((utf >> 6) & 0x3F) | 0x80);
				ret += (char)(((utf >> 0) & 0x3F) | 0x80);
			}
			else {
				ret = "";
			}

			return ret;
		};

		InputManager::Data* p = (InputManager::Data*)(glfwGetWindowUserPointer(window));
		p->m_text = utf8convert(codepoint);
	}


	InputManager::InputManager() :
		m_data{ Cursor{0.0, 0.0, 0.0, 0.0, 0.0, false}, ""}
	{
		Update();
	}



	const InputManager::Cursor& InputManager::GetCursor() const
	{
		return m_data.m_cursor;
	}


	const std::string& InputManager::GetText() const
	{
		return m_data.m_text;
	}


	void InputManager::Update()
	{
		GLFWwindow* window = glfwGetCurrentContext();
		if (window)
		{
			m_data.m_text = "";

			UpdateCursorPos(window);
			UpdateMouseDown(window);

			glfwSetWindowUserPointer(window, &m_data);
			glfwSetCharCallback(window, GLFWCharacterCallback);
			glfwSetScrollCallback(window, GLFWScrollCallback);
			glfwSetKeyCallback(window, GLFWKeyCallback);
		}
	}


	void InputManager::UpdateCursorPos(GLFWwindow* window)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		double dx = m_data.m_cursor.x - x;
		double dy = m_data.m_cursor.y - y;

		m_data.m_cursor.x = x;
		m_data.m_cursor.y = height - y;
		m_data.m_cursor.xdelta = dx;
		m_data.m_cursor.ydelta = dy;
	}


	void InputManager::UpdateMouseDown(GLFWwindow* window)
	{
		int button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
		if (button == GLFW_PRESS)
		{
			m_data.m_cursor.leftMouseDown = true;
		}

		else
		{
			m_data.m_cursor.leftMouseDown = false;
		}
	}
}
