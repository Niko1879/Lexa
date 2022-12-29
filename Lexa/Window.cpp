#include <locale>
#include <windows.h>
#include "Window.h"

namespace Lexa
{
	static std::weak_ptr<WindowEventManager> s_CurrentEventManager;


	void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		if (!s_CurrentEventManager.expired())
			s_CurrentEventManager.lock()->HandleWindowResizeCallbacks(width, height);
	}


	void GLFWScrollCallback(GLFWwindow* window, double dx, double dy)
	{
		if (!s_CurrentEventManager.expired())
			s_CurrentEventManager.lock()->HandleScrollCallbacks(dx, dy);
	}


	void GLFWMouseClickCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (!s_CurrentEventManager.expired())
			s_CurrentEventManager.lock()->HandleMouseButtonCallbacks(button, action, mods);
	}


	void GLFWFrameCallback(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (!s_CurrentEventManager.expired())
			s_CurrentEventManager.lock()->HandleFrameCallbacks();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

		if (!s_CurrentEventManager.expired())
			s_CurrentEventManager.lock()->HandleCharacterCallbacks(utf8convert(static_cast<char32_t>(codepoint)));
	}


	Window::Window(int width, int height) : m_window(nullptr, [](GLFWwindow* ptr) {glfwDestroyWindow(ptr); }),
										    m_width(width),
											m_height(height),
										    m_eventManager(std::make_shared<WindowEventManager>()),
											m_onNextFrame(new OnWindowRefresh(*this)),
											m_onWindowResize(new OnWindowResize(*this)),
											m_onMouseClick(new OnMouseClick(*this)),
										    m_cursor{0.0, 0.0, 0.0, 0.0, false}
	{
		m_window.reset((glfwCreateWindow(width, height, "Lexa", nullptr, nullptr)));

		if (!glfwGetCurrentContext())
		{
			MakeCurrent();
		}

		m_eventManager->AddWindowResizeCallback(m_onWindowResize);
		m_eventManager->AddMouseButtonCallback(m_onMouseClick);
		m_eventManager->AddFrameCallback(m_onNextFrame);
	}


	void Window::MakeCurrent()
	{
		glfwMakeContextCurrent(m_window.get());
		SetCallbacks();
		s_CurrentEventManager = m_eventManager;
	}


	void Window::Update()
	{
		GLFWFrameCallback(m_window.get());
	}


	int Window::GetWidth() const
	{
		return m_width;
	}


	int Window::GetHeight() const
	{
		return m_height;
	}


	std::pair<float, float>  Window::GetCursorPos() const
	{
		return std::make_pair(m_cursor.m_x, m_cursor.m_y);
	}


	std::pair<float, float>  Window::GetCursorDelta() const
	{
		return std::make_pair(m_cursor.m_xdelta, m_cursor.m_ydelta);
	}


	bool Window::GetMouseDown() const
	{
		return m_cursor.m_mouseDown;
	}


	void Window::AddWindowResizeCallback(const std::shared_ptr<WindowResizeCallback>& callback)
	{
		m_eventManager->AddWindowResizeCallback(callback);
	}


	void Window::AddScrollCallback(const std::shared_ptr<ScrollCallback>& callback)
	{
		m_eventManager->AddScrollCallback(callback);
	}


	void Window::AddMouseButtonCallback(const std::shared_ptr<MouseButtonCallback>& callback)
	{
		m_eventManager->AddMouseButtonCallback(callback);
	}


	void Window::AddFrameCallback(const std::shared_ptr<FrameCallback>& callback)
	{
		m_eventManager->AddFrameCallback(callback);
	}


	void Window::AddCharacterCallback(const std::shared_ptr<CharacterCallback>& callback)
	{
		m_eventManager->AddCharacterCallback(callback);
	}


	void Window::UpdateMouseDown(int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (GLFW_PRESS == action)
			{
				m_cursor.m_mouseDown = true;
			}

			else if (GLFW_RELEASE == action)
			{
				m_cursor.m_mouseDown = false;
			}
		}
	}


	void Window::UpdateCursorPos()
	{
		double xNew, yNew;
		glfwGetCursorPos(m_window.get(), &xNew, &yNew);
		yNew = m_height - yNew;
		m_cursor.m_xdelta = xNew - m_cursor.m_x;
		m_cursor.m_ydelta = yNew - m_cursor.m_y;
		m_cursor.m_x = xNew;
		m_cursor.m_y = yNew;
	}


	void Window::UpdateWindowSize(int width, int height)
	{
		m_width = width;
		m_height = height;
	}


	Window::OnMouseClick::OnMouseClick(Window& parent) : m_parent(parent) {}


	void Window::OnMouseClick::Execute(int button, int action, int mods)
	{
		m_parent.UpdateMouseDown(button, action, mods);
	}


	Window::OnWindowRefresh::OnWindowRefresh(Window& parent) : m_parent(parent) {}


	void Window::OnWindowRefresh::Execute()
	{
		m_parent.UpdateCursorPos();
	}


	Window::OnWindowResize::OnWindowResize(Window& parent) : m_parent(parent) {}


	void Window::OnWindowResize::Execute(int width, int height)
	{
		m_parent.UpdateWindowSize(width, height);
	}


	void Window::SetCallbacks() const
	{
		glfwSetFramebufferSizeCallback(m_window.get(), GLFWFramebufferSizeCallback);
		glfwSetScrollCallback(m_window.get(), GLFWScrollCallback);
		glfwSetMouseButtonCallback(m_window.get(), GLFWMouseClickCallback);
		glfwSetCharCallback(m_window.get(), GLFWCharacterCallback);
	}
}
