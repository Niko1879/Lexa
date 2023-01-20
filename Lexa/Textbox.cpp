#include <numeric>

#include "Textbox.h"


namespace Lexa
{
	size_t Advance(const std::string& str, size_t index, size_t amount)
	{
		char first = 0x80;
		char second = 0x40;
		size_t n = index;
		while (n < amount && index < str.size())
		{
			++index;
			char c;
			while (((c = str[index]) != '\0') && (c & first) && !(c & second))
			{
				++index;
			}
			++n;
		}

		return index;
	}


	std::string SubstrUtf8(const std::string& str, size_t start, size_t count)
	{
		return str.substr(Advance(str, 0, start), Advance(str, start, count));
	}


	void PopBackUtf8(std::string& str)
	{
		char first = 0x80;
		char second = 0x40;
		char c;
		while (((c = str.back()) & first) && !(c & second))
			str.pop_back();
		str.pop_back();
	}


	std::string GetCharUtf8(const std::string& str, size_t index)
	{
		std::string res = std::string(1, str[index]);
		++index;
		char first = 0x80;
		char second = 0x40;
		char c;
		while (((c = str[index]) != '\0') && (c & first) && !(c & second))
		{
			res += c;
			++index;
		}

		return res;
	}


	Textbox::Textbox(int width, int height, int x, int y, const std::string& font, int fontSize, float fontScale) :
		m_width(width), 
		m_height(height), 
		m_active(false),
		m_x(x),
		m_y(y),
		m_text(""),
		m_font(font),
		m_fontSize(fontSize),
		m_cursorIdx(0),
		m_cursorPos(x),
		m_cursorOffset(0.f),
		m_fontScale(fontScale)
	{

	}


	const std::string& Textbox::GetText() const
	{
		return m_text;
	}


	int Textbox::GetWidth() const
	{
		return m_width;
	}


	int Textbox::GetHeight() const
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


	int Textbox::GetCursorIdx() const
	{
		return std::min(m_cursorIdx, (int)m_text.size() - 1);
	}


	int Textbox::GetCursorPos() const
	{
		return m_cursorPos;
	}


	float Textbox::GetFontScale() const
	{
		return m_fontScale;
	}


	void Textbox::SetActive(bool active)
	{
		m_active = active;
	}


	void Textbox::SetCursorPos(float x, float y, const TextManager& textManager)
	{
		float cumulative = m_x;
		int idx = -1;

		for (float i : m_charWidths)
		{
			cumulative += i;
			++idx;
			if (cumulative > x)
			{
				float prev = cumulative - i;
				if (x - prev < cumulative - x)
				{
					--idx;
					cumulative = prev;
				}
				break;
			}
		}

		m_cursorIdx = idx;
		if (idx == -1)
		{
			m_cursorPos = m_x;
		}

		else
		{
			m_cursorPos = cumulative;
			AlignCursor(textManager);
		}
	}


	void Textbox::SetPosition(int x, int y)
	{
		m_x = x;
		m_y = y;
	}


	void Textbox::AddText(const std::string& text, const TextManager& textManager)
	{
		if (!m_active || text.empty())
			return;

		const Font& font = textManager.GetFont(m_font, m_fontSize);

		int substr = m_cursorIdx + 1;
		std::string left = SubstrUtf8(m_text, 0, substr);
		std::string right = SubstrUtf8(m_text, substr, m_text.size());

		auto it = m_charWidths.begin();

		if (text == "\b")
		{
			if (!left.empty())
			{
				PopBackUtf8(left);
				int idx = std::max(0, m_cursorIdx);
				std::advance(it, idx);
				m_cursorPos -= *it;
				m_charWidths.erase(it);
				--m_cursorIdx;
			}
		}

		else if (IsWithinBounds(text, textManager))
		{
			left += text;
			float x = m_fontScale * font.charInfo.at(text).xOffset;
			std::advance(it, std::max(0, m_cursorIdx + 1));
			if (it == m_charWidths.end())
			{
				m_charWidths.push_back(x);
			}
			else
			{
				m_charWidths.insert(it, x);
			}
			++m_cursorIdx;
			m_cursorPos += x;
		}

		m_text = left + right;
		AlignCursor(textManager);
	}


	bool Textbox::IsWithinBounds(const std::string& toAppend, const TextManager& textManager) const
	{
		float sum = std::accumulate(m_charWidths.begin(), m_charWidths.end(), 0);
		sum += m_fontScale * textManager.GetFont(m_font, m_fontSize).charInfo.at(toAppend).xOffset;
		return sum < m_width;
	}


	void Textbox::AlignCursor(const TextManager& textManager)
	{
		std::string ch = GetCharUtf8(m_text, Advance(m_text, 0, m_cursorIdx));
		const Font& font = textManager.GetFont(m_font, m_fontSize);
		int width = font.textureAtlas.GetTextureData(ch).width;
		int xOffset = font.charInfo.at(ch).xOffset;
		float delta = m_fontScale * (xOffset - width);
		m_cursorPos = m_cursorPos + m_cursorOffset - delta;
		m_cursorOffset = delta;
	}
}
