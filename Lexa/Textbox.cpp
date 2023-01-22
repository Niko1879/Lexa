#include <numeric>

#include "Textbox.h"


namespace Lexa
{
	size_t Advance(const std::string& str, size_t index, size_t amount)
	{
		char first = 0x80;
		char second = 0x40;
		size_t n = 0;
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
		while (index <= str.size() && ((c = str[index]) != '\0') && (c & first) && !(c & second))
		{
			res += c;
			++index;
		}

		return res;
	}


	Textbox::Textbox(int width, int height, int x, int y, const std::string& font, int fontSize, float fontScale) :
		m_text(""),
		m_font(font),
		m_fontSize(fontSize),
		m_width(width), 
		m_height(height), 
		m_x(x),
		m_y(y),
		m_cursorIdx(0),
		m_cursorPos(x),
		m_highlightIdxStart(0),
		m_highlightIdxEnd(0),
		m_highlightStart(0.f),
		m_highlightEnd(0.f),
		m_cursorOffset(0.f),
		m_fontScale(fontScale),
		m_active(false)
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


	std::pair<int, int> Textbox::GetHighlightRegion() const
	{
		return std::make_pair(std::min(m_highlightStart, m_highlightEnd), std::max(m_highlightStart, m_highlightEnd));
	}


	void Textbox::SetActive(bool active)
	{
		m_active = active;
	}


	void Textbox::SetCursorPos(float x, float y)
	{
		auto [cumulative, idx] = ClampCursorToText(x);

		m_cursorIdx = idx;
		if (idx == -1)
		{
			m_cursorPos = m_x;
		}

		else
		{
			m_cursorPos = cumulative;
		}

		EndHighlightRegion();
	}


	void Textbox::SetPosition(int x, int y)
	{
		m_x = x;
		m_y = y;
	}


	void Textbox::BeginHighlightRegion()
	{
		m_highlightIdxStart = m_cursorIdx;
		m_highlightStart = m_cursorPos;
		m_highlightIdxEnd = m_cursorIdx;
		m_highlightEnd = m_cursorPos;
	}


	void Textbox::EndHighlightRegion()
	{
		m_highlightIdxEnd = m_cursorIdx;
		m_highlightEnd = m_cursorPos;
	}


	void Textbox::AddText(const std::string& text, const TextManager& textManager)
	{
		bool doHighlight = m_highlightIdxStart != m_highlightIdxEnd;
		if (doHighlight)
			EraseHighlightedRegion(textManager);

		if (m_active && !text.empty())
		{
			size_t idx = 0;
			std::string ch;

			while ((ch = GetCharUtf8(text, idx++))[0] != '\0')
			{
				if (ch == "\b")
				{
					if (!doHighlight)
						EraseChar(textManager);
				}

				else
				{
					AddChar(ch, textManager);
				}
			}
		}
	}

	void Textbox::AdvanceCursor(int amount)
	{
		bool dir = amount >= 0;
		for (int i = std::min(0, amount); i <= std::max(0, amount); ++i)
		{
			AdvanceCursor(dir);
		}
	}


	void Textbox::AddChar(const std::string& ch, const TextManager& textManager)
	{
		float x = m_fontScale * textManager.GetFont(m_font, m_fontSize).charInfo.at(ch).xOffset;
		std::list<float>::iterator it = m_charWidths.begin();
		std::advance(it, std::min((int)m_charWidths.size(), m_cursorIdx + 1));

		std::string left = SubstrUtf8(m_text, 0, m_cursorIdx + 1);
		std::string right = SubstrUtf8(m_text, m_cursorIdx + 1, m_text.size());

		if (it == m_charWidths.end())
		{
			m_charWidths.push_back(x);
		}

		else
		{
			m_charWidths.insert(it, x);
		}

		m_text = left + ch + right;
		AdvanceCursor(true);
	}


	void Textbox::EraseChar(const TextManager& textManager)
	{
		std::string left = SubstrUtf8(m_text, 0, m_cursorIdx + 1);
		std::string right = SubstrUtf8(m_text, m_cursorIdx + 1, m_text.size());

		float x = m_fontScale * textManager.GetFont(m_font, m_fontSize).charInfo.at(GetCharUtf8(m_text, m_text.size() - 1)).xOffset;
		std::list<float>::iterator it = m_charWidths.begin();
		std::advance(it, std::max(0, m_cursorIdx));
		PopBackUtf8(left);
		m_text = left + right;
		AdvanceCursor(false);
		m_charWidths.erase(it);
	}


	void Textbox::AdvanceCursor(bool dir)
	{
		if (((m_cursorIdx < 0) && !dir) || ((m_cursorIdx == m_text.size() - 1) && dir))
			return;

		int nextCharIdx = dir ? m_cursorIdx + 1 : m_cursorIdx;
		std::list<float>::iterator it = m_charWidths.begin();
		std::advance(it, (std::min(std::max(nextCharIdx, 0), (int)m_charWidths.size())));
		float x =  *it;
		dir ? m_cursorPos += x : m_cursorPos -= x;
		dir ? ++m_cursorIdx : --m_cursorIdx;
	}


	bool Textbox::IsWithinBounds(const std::string& toAppend, const TextManager& textManager) const
	{
		float sum = std::accumulate(m_charWidths.begin(), m_charWidths.end(), 0);
		sum += m_fontScale * textManager.GetFont(m_font, m_fontSize).charInfo.at(toAppend).xOffset;
		return sum < m_width;
	}


	std::pair<float, int> Textbox::ClampCursorToText(float cursorX) const
	{
		float cumulative = m_x;
		int idx = -1;

		for (float i : m_charWidths)
		{
			cumulative += i;
			++idx;
			if (cumulative > cursorX)
			{
				float prev = cumulative - i;
				if (cursorX - prev < cumulative - cursorX)
				{
					--idx;
					cumulative = prev;
				}
				break;
			}
		}

		return std::make_pair(cumulative, idx);
	}


	void Textbox::EraseHighlightedRegion(const TextManager& textManager)
	{
		int start = std::min(m_highlightIdxStart, m_highlightIdxEnd);
		int end = std::max(m_highlightIdxStart, m_highlightIdxEnd);
		
		if (m_cursorIdx == end)
		{
			while (m_cursorIdx > start)
			{
				EraseChar(textManager);
			}
		}

		else if (m_cursorIdx == start)
		{
			while (m_cursorIdx < end)
				AdvanceCursor(true);
			for (int i = start; i < end; ++i)
			{
				EraseChar(textManager);
			}
		}

		BeginHighlightRegion();
	}
}
