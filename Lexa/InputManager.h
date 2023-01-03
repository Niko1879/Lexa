#pragma once
#include <string>
#include <tuple>

#include "Window.h"


namespace Lexa
{
	class InputManager
	{
	public:
		InputManager();

		void Update();

		struct Cursor
		{
			double m_x;
			double m_y;
			double m_xdelta;
			double m_ydelta;
			double m_scrolldelta;
			bool m_leftMouseDown;
		};

		struct Data
		{
			Cursor m_cursor;
			std::string m_text;
		};

		const Cursor& GetCursor() const;

		const std::string& GetText() const;

	private:
		void UpdateCursorPos(GLFWwindow* window);

		void UpdateMouseDown(GLFWwindow* window);

		Data m_data;
	};
}

