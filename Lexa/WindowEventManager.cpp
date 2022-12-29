#include "WindowEventManager.h"
#include "GLFW/glfw3.h"

namespace Lexa
{
	template<class T>
	void _DoDelete(std::vector<std::weak_ptr<T>>& vec)
	{
		std::vector<int> toDelete;

		for (int i = 0; i < vec.size(); ++i)
		{
			std::weak_ptr<T>& c = vec[i];

			if (c.expired())
			{
				toDelete.push_back(i);
			}
		}

		for (int i : toDelete)
		{
			vec.erase(vec.begin() + i);
		}
	}


	WindowEventManager::WindowEventManager() 
	{
	
	}


	void WindowEventManager::AddWindowResizeCallback(const std::shared_ptr<WindowResizeCallback>& callback)
	{
		m_windowResizedCallbacks.emplace_back(callback);
	}


	void WindowEventManager::AddScrollCallback(const std::shared_ptr<ScrollCallback>& callback)
	{
		m_scrollCallbacks.emplace_back(callback);
	}


	void WindowEventManager::AddMouseButtonCallback(const std::shared_ptr<MouseButtonCallback>& callback)
	{
		m_mouseButtonCallbacks.emplace_back(callback);
	}


	void WindowEventManager::AddFrameCallback(const std::shared_ptr<FrameCallback>& callback)
	{
		m_frameCallbacks.emplace_back(callback);
	}


	void WindowEventManager::AddCharacterCallback(const std::shared_ptr<CharacterCallback>& callback)
	{
		m_characterCallbacks.emplace_back(callback);
	}


	void WindowEventManager::HandleWindowResizeCallbacks(int width, int height)
	{
		_DoDelete(m_windowResizedCallbacks);
		std::for_each(m_windowResizedCallbacks.begin(), m_windowResizedCallbacks.end(), [=](std::weak_ptr<WindowResizeCallback>& c) {c.lock()->Execute(width, height); });
	}


	void WindowEventManager::HandleScrollCallbacks(double dx, double dy)
	{
		_DoDelete(m_scrollCallbacks);
		std::for_each(m_scrollCallbacks.begin(), m_scrollCallbacks.end(), [=](std::weak_ptr<ScrollCallback>& c) {c.lock()->Execute(dx, dy); });
	}


	void WindowEventManager::HandleMouseButtonCallbacks(int button, int action, int mods)
	{
		_DoDelete(m_mouseButtonCallbacks);
		std::for_each(m_mouseButtonCallbacks.begin(), m_mouseButtonCallbacks.end(), [=](std::weak_ptr<MouseButtonCallback>& c) {c.lock()->Execute(button, action, mods); });
	}


	void WindowEventManager::HandleFrameCallbacks()
	{
		_DoDelete(m_frameCallbacks);
		std::for_each(m_frameCallbacks.begin(), m_frameCallbacks.end(), [=](std::weak_ptr<FrameCallback>& c) {c.lock()->Execute(); });
	}


	void WindowEventManager::HandleCharacterCallbacks(std::string ch)
	{
		_DoDelete(m_characterCallbacks);
		std::for_each(m_characterCallbacks.begin(), m_characterCallbacks.end(), [=](std::weak_ptr<CharacterCallback>& c) {c.lock()->Execute(ch); });
	}
}