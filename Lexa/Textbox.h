#pragma once

#include <string>
#include <list>
#include "TextManager.h"


namespace Lexa
{
	class Textbox
	{
	public:
		Textbox(int width, int height, int x, int y, const std::string& font, int fontSize, float fontScale);

		const std::string& GetText() const;

		int GetWidth() const;
		
		int GetHeight() const;

		std::pair<int, int> GetPosition() const;

		int GetCursorIdx() const;

		const std::string& GetFont() const;

		int GetFontSize() const;

		int GetCursorPos() const;

		float GetFontScale() const;

		void SetActive(bool active);

		void SetCursorPos(float x, float y, const TextManager& textManager);

		void SetPosition(int x, int y);

		void AddText(const std::string& text, const TextManager& textManager);

	private:
		bool IsWithinBounds(const std::string& toAppend, const TextManager& textManager) const;

		void AlignCursor(const TextManager& textManager);

		std::string m_text;
		std::string m_font;
		int m_fontSize;
		int m_width;
		int m_height;
		int m_x;
		int m_y;
		int m_cursorIdx;
		float m_cursorPos;
		float m_cursorOffset;
		bool m_active;
		float m_fontScale;
		std::list<float> m_charWidths;
	};
}
