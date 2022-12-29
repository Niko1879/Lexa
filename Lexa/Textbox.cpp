#include "TextManager.h"
#include "Textbox.h"


namespace Lexa
{
	Textbox::Textbox(int width, int height, int x, int y, const std::shared_ptr<Window>& context) :
		m_width(width), 
		m_height(height), 
		m_active(false),
		m_x(x),
		m_y(y),
		m_context(context),
		m_text(""),
		m_OnKeyPress(new OnKeyPress(*this)),
		m_OnMouseClick(new OnMouseClick(*this))
	{
		SetContext(context);
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


	void Textbox::SetContext(const std::shared_ptr<Window>& window)
	{
		window->AddMouseButtonCallback(m_OnMouseClick);
		window->AddCharacterCallback(m_OnKeyPress);

		m_context = window;
	}


	Textbox::OnMouseClick::OnMouseClick(Textbox& parent) : m_parent(parent) {}


	void Textbox::OnMouseClick::Execute(int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			std::shared_ptr<Window> context = m_parent.m_context.lock();
			std::pair<float, float> cursorPos = context->GetCursorPos();

			m_parent.UpdateActive(cursorPos.first, cursorPos.second);
		}
	}


	Textbox::OnKeyPress::OnKeyPress(Textbox& parent) : m_parent(parent) {}


	void Textbox::OnKeyPress::Execute(std::string ch)
	{
		if (m_parent.m_active)
		{
			m_parent.m_text += ch;
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