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
			double x;
			double y;
			double xdelta;
			double ydelta;
			double scrolldelta;
			bool leftMouseDown;
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

