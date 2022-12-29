#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "WindowEventManager.h"

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

		std::pair<float, float> GetCursorPos() const;

		std::pair<float, float> GetCursorDelta() const;

		bool GetMouseDown() const;
		
		void AddWindowResizeCallback(const std::shared_ptr<WindowResizeCallback>& callback);

		void AddScrollCallback(const std::shared_ptr<ScrollCallback>& callback);

		void AddMouseButtonCallback(const std::shared_ptr<MouseButtonCallback>& callback);

		void AddFrameCallback(const std::shared_ptr<FrameCallback>& callback);

		void AddCharacterCallback(const std::shared_ptr<CharacterCallback>& callback);

	private:
		std::shared_ptr<WindowEventManager> m_eventManager;

		struct OnWindowResize : public WindowResizeCallback
		{
			OnWindowResize(Window& parent);
			void Execute(int width, int height) override;
			Window& m_parent;
		};
		std::shared_ptr<WindowResizeCallback> m_onWindowResize;

		struct OnMouseClick : public MouseButtonCallback
		{
			OnMouseClick(Window& parent);
			void Execute(int button, int action, int mods) override;
			Window& m_parent;
		};
		std::shared_ptr< MouseButtonCallback> m_onMouseClick;

		struct OnWindowRefresh : public FrameCallback
		{
			OnWindowRefresh(Window& parent);
			void Execute() override;
			Window& m_parent;
		};
		std::shared_ptr<FrameCallback> m_onNextFrame;

		void UpdateMouseDown(int button, int action, int mods);

		void UpdateCursorPos();

		void UpdateWindowSize(int width, int height);

		void SetCallbacks() const;

		std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;

		int m_width;

		int m_height;

		struct Cursor
		{
			double m_x;
			double m_y;
			double m_xdelta;
			double m_ydelta;
			bool m_mouseDown;
		} 
		m_cursor;
	};
}
