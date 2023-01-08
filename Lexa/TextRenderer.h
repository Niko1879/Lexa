#pragma once

#include "Textbox.h"
#include "VertexBuffer.h"
#include "Window.h"


namespace Lexa
{
	class TextRenderer
	{
	public:
		TextRenderer();

		const VertexBuffer& GetGeometry() const;

		void Generate(const Textbox& textbox, const TextManager& textManager, const Window& context);

	private:
		VertexBuffer m_vao;
	};
}
