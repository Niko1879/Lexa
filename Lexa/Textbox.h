#pragma once

#include <string>
#include "WindowEventManager.h"
#include "Window.h"

namespace Lexa
{
	class Textbox
	{
	public:
		Textbox(int width, int height, int x, int y, const std::shared_ptr<Window>& context);

		const std::string& GetText() const;

		float GetWidth() const;
		
		float GetHeight() const;

		std::pair<int, int> GetPosition() const;

		void SetContext(const std::shared_ptr<Window>& window);

	private:
		struct OnMouseClick : public MouseButtonCallback
		{
			OnMouseClick(Textbox& parent);

			void Execute(int button, int action, int mods) override;

			Textbox& m_parent;
		};
		std::shared_ptr<MouseButtonCallback> m_OnMouseClick;

		struct OnKeyPress : public CharacterCallback
		{
			OnKeyPress(Textbox& parent);

			void Execute(std::string ch) override;

			Textbox& m_parent;
		};
		std::shared_ptr<CharacterCallback> m_OnKeyPress;

		void UpdateActive(float x, float y);

		std::string m_text;
		int m_width;
		int m_height;
		int m_x;
		int m_y;
		bool m_active;
		std::weak_ptr<Window> m_context;
	};
}

