#pragma once
#include "VertexBuffer.h"
#include "Window.h"


namespace Lexa
{
	class QuadRenderer
	{
	public:
		QuadRenderer();

		const VertexBuffer& GetGeometry() const;

		void Generate(int x, int y, int width, int height, const Window& context);

	private:
		VertexBuffer m_vao;
	};
}

