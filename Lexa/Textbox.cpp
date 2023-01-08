#include "Textbox.h"


namespace Lexa
{
	Textbox::Textbox(int width, int height, int x, int y, const std::string& font, int fontSize) :
		m_width(width), 
		m_height(height), 
		m_active(false),
		m_x(x),
		m_y(y),
		m_text(""),
		m_font(font),
		m_fontSize(fontSize),
		m_cursorIdx(0),
		m_totalTextWidth(0)
	{

	}


	const std::string& Textbox::GetText() const
	{
		return m_text;
	}


	float Textbox::GetWidth() const
	{
		return m_width;
	}


	float Textbox::GetHeight() const
	{
		return m_height;
	}


	std::pair<int, int> Textbox::GetPosition() const
	{
		return std::make_pair(m_x, m_y);
	}


	const std::string& Textbox::GetFont() const
	{
		return m_font;
	}


	int Textbox::GetFontSize() const
	{
		return m_fontSize;
	}


	void Textbox::SetActive(bool active)
	{
		m_active = active;
	}


	void Textbox::SetCursorPos(float x, float y)
	{
		int cumulative = 0;
		int idx = 0;

		for (int i : m_charWidths)
		{
			cumulative += i;
			++idx;
			if (cumulative > x)
			{
				int prev = cumulative - i;
				if (x - prev < cumulative - x)
				{
					--idx;
				}
				break;
			}
		}

		m_cursorIdx = idx;
	}


	void Textbox::AddText(const std::string& text, const TextManager& textManager)
	{
		if (text.empty())
			return;

		std::string left = m_text.substr(0, m_cursorIdx);
		std::string right = m_cursorIdx >= m_text.size() ? "" : m_text.substr(m_cursorIdx);

		auto it = m_charWidths.begin();

		if (text == "\b")
		{
			if (!left.empty())
			{
				left.pop_back();
				int idx = std::min((unsigned long long)m_cursorIdx, m_charWidths.size() - 1);
				std::advance(it, idx);
				m_charWidths.erase(it);
				--m_cursorIdx;
			}
		}

		else
		{
			left += text;
			int x = textManager.GetCharInfo(m_font, m_fontSize, text).xOffset;
			std::advance(it, m_cursorIdx);
			if (it == m_charWidths.end())
			{
				m_charWidths.push_back(x);
			}
			else
			{
				m_charWidths.insert(it, x);
			}
			++m_cursorIdx;
		}

		m_text = left + right;
	}
}