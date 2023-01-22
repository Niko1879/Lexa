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

		void SetCursorPos(float x, float y);

		void SetPosition(int x, int y);

		void BeginHighlightRegion();

		void EndHighlightRegion();

		void AddText(const std::string& text, const TextManager& textManager);

		void AdvanceCursor(int amount);

	private:
		void AddChar(const std::string& ch, const TextManager& textManager);

		void EraseChar(const TextManager& textManager);

		void AdvanceCursor(bool dir);

		bool IsWithinBounds(const std::string& toAppend, const TextManager& textManager) const;

		std::pair<float, int> ClampCursorToText(float cursorX) const;

		void EraseHighlightedRegion();

		std::string m_text;
		std::string m_font;
		int m_fontSize;
		int m_width;
		int m_height;
		int m_x;
		int m_y;
		int m_cursorIdx;
		int m_highlightIdxStart;
		int m_highlightIdxEnd;
		float m_highlightStart;
		float m_highlightEnd;
		float m_cursorPos;
		float m_cursorOffset;
		float m_fontScale;
		bool m_active;
		bool m_highlight;
		std::list<float> m_charWidths;
	};
}
