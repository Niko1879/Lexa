#include "QuadRenderer.h"


namespace Lexa
{
	QuadRenderer::QuadRenderer() : m_vao(std::vector<int>{2}) {}


	const VertexBuffer& QuadRenderer::GetGeometry() const
	{
		return m_vao;
	}


	void QuadRenderer::Generate(int x, int y, int width, int height, const Window& context)
	{
        float scrWidth = context.GetWidth();
        float scrHeight = context.GetHeight();

        float xx = 2.f * x / scrWidth - 1.f;
        float yy = 2.f * y / scrHeight - 1.f;
        float XX = xx + 2.f * width / scrWidth;
        float YY = yy + 2.f * height / scrHeight;

        std::vector<float> vertices
        {
            xx, yy, //bottomleft
            xx, YY, //topleft
            XX, YY, //topright,
            XX, yy  //bottomright
        };

        std::vector<unsigned> indices
        {
            2, 1, 0,
            0, 3, 2
        };

        m_vao.SetVertexData(vertices);
        m_vao.SetIndexData(indices);
	}
}
