#pragma once

#include <string>


namespace Lexa
{
	class Textbox
	{
	public:
		Textbox(int width, int height, int x, int y);

		const std::string& GetText() const;

		float GetWidth() const;
		
		float GetHeight() const;

		std::pair<int, int> GetPosition() const;

		void Update(bool mouseDown, float cursorX, float cursorY, const std::string& text);

	private:
		void UpdateActive(float x, float y);

		void UpdateCursorPos(bool leftArrowDown);

		std::string m_text;
		int m_width;
		int m_height;
		int m_x;
		int m_y;
		bool m_active;
		int m_pos;
		int m_perCharWidth;
	};
}

