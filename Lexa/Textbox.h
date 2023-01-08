#pragma once

#include <string>
#include <list>
#include "TextManager.h"


namespace Lexa
{
	class Textbox
	{
	public:
		Textbox(int width, int height, int x, int y, const std::string& font, int fontSize);

		const std::string& GetText() const;

		float GetWidth() const;
		
		float GetHeight() const;

		std::pair<int, int> GetPosition() const;

		const std::string& GetFont() const;

		int GetFontSize() const;

		void SetActive(bool active);

		void SetCursorPos(float x, float y);

		void AddText(const std::string& text, const TextManager& textManager);

	private:
		std::string m_text;
		std::string m_font;
		int m_fontSize;
		int m_width;
		int m_height;
		int m_x;
		int m_y;
		int m_cursorIdx;
		bool m_active;
		std::list<int> m_charWidths;
		int m_totalTextWidth;
	};
}

