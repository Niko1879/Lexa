#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <string>


namespace Lexa
{
	class WindowResizeCallback
	{
	public:
		virtual void Execute(int width, int height) = 0;

	private:
	};


	class ScrollCallback
	{
	public:
		virtual void Execute(double dx, double dy) = 0;
	};


	class MouseButtonCallback
	{
	public:
		virtual void Execute(int button, int action, int mods) = 0;
	};


	class FrameCallback
	{
	public:
		virtual void Execute() = 0;
	};


	class CharacterCallback
	{
	public:
		virtual void Execute(std::string ch) = 0;
	};


	class WindowEventManager
	{
	public:
		WindowEventManager();

		WindowEventManager(const WindowEventManager& other) = delete;

		WindowEventManager& operator=(const WindowEventManager& other) = delete;

		void AddWindowResizeCallback(const std::shared_ptr<WindowResizeCallback>& callback);
		
		void AddScrollCallback(const std::shared_ptr<ScrollCallback>& callback);

		void AddMouseButtonCallback(const std::shared_ptr<MouseButtonCallback>& callback);

		void AddFrameCallback(const std::shared_ptr<FrameCallback>& callback);

		void AddCharacterCallback(const std::shared_ptr<CharacterCallback>& callback);

		void HandleWindowResizeCallbacks(int width, int height);

		void HandleScrollCallbacks(double dx, double dy);

		void HandleMouseButtonCallbacks(int button, int action, int mods);

		void HandleFrameCallbacks();

		void HandleCharacterCallbacks(std::string ch);
	
	private:
		std::vector<std::weak_ptr<WindowResizeCallback>> m_windowResizedCallbacks;
		std::vector<std::weak_ptr<ScrollCallback>> m_scrollCallbacks;
		std::vector<std::weak_ptr<MouseButtonCallback>> m_mouseButtonCallbacks;
		std::vector<std::weak_ptr<FrameCallback>> m_frameCallbacks;
		std::vector<std::weak_ptr<CharacterCallback>> m_characterCallbacks;
	};
}

