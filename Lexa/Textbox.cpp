#include "Textbox.h"


namespace Lexa
{
	Textbox::Textbox(int width, int height, int x, int y) :
		m_width(width), 
		m_height(height), 
		m_active(false),
		m_x(x),
		m_y(y),
		m_text("")
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


	void Textbox::Update(bool mouseDown, float cursorX, float cursorY, const std::string& text)
	{
		if (mouseDown)
		{
			UpdateActive(cursorX, cursorY);
		}

		if (m_active)
		{
			m_text += text;
		}
	}


	void Textbox::UpdateActive(float x, float y)
	{
		if (m_x <= x && x <= m_x + m_width &&
			m_y <= y && y <= m_y + m_height)
		{
			m_active = true;
		}

		else
		{
			m_active = false;
		}
	}
}