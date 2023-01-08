#pragma once

#include <memory>
#include "Textbox.h"
#include "VertexBuffer.h"
#include "Window.h"


namespace Lexa
{
	class TextRenderer
	{
	public:
		TextRenderer();

		std::shared_ptr<const VertexBuffer> GetGeometry() const;

		void Update(const Textbox& textbox, const TextManager& textManager, const Window& context);

	private:
		std::shared_ptr<VertexBuffer> m_vao;
	};
}

