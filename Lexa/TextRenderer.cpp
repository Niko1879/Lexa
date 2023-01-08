#include "TextRenderer.h"


namespace Lexa
{
    TextRenderer::TextRenderer() : m_vao(std::vector<int>{2, 2}, VertexBuffer::Format::DYNAMIC)
    {

    }


	const VertexBuffer& TextRenderer::GetGeometry() const
	{
        return m_vao;
	}

    
    void TextRenderer::Generate(const Textbox& textbox, const TextManager& textManager, const Window& context)
    {
        const std::string& text = textbox.GetText();
        const std::string& font = textbox.GetFont();
        int fontSize = textbox.GetFontSize();

        std::pair<int, int> pos = textbox.GetPosition();
        float xpos = 2.f * pos.first / (float)context.GetWidth() - 1.f;
        float ypos = 2.f * pos.second / (float)context.GetHeight() - 1.f;

        std::vector<float> vertices;
        std::vector<unsigned> indices;
        int index = 0;

        for (char c : textbox.GetText())
        {
            std::string ch(1, c);

            TextureAtlas::TextureInfo texData = textManager.GetFont(font, fontSize).GetTextureData(ch);
            const TextManager::CharInfo& charInfo = textManager.GetCharInfo(font, fontSize, ch);

            float yoffset = 2.f * charInfo.yOffset / (float)context.GetHeight();
            float oldy = ypos;
            ypos = ypos - yoffset;

            //bottomleft
            vertices.push_back(xpos);
            vertices.push_back(ypos);
            vertices.push_back(texData.bottomLeftU);
            vertices.push_back(texData.bottomLeftV);

            //topleft
            vertices.push_back(xpos);
            vertices.push_back(ypos + 2.f * (float)texData.height / context.GetHeight());
            vertices.push_back(texData.topLeftU);
            vertices.push_back(texData.topLeftV);

            //topright
            vertices.push_back(xpos + 2.f * (float)texData.width / context.GetWidth());
            vertices.push_back(ypos + 2.f * (float)texData.height / context.GetHeight());
            vertices.push_back(texData.topRightU);
            vertices.push_back(texData.topRightV);

            //bottomright
            vertices.push_back(xpos + 2.f * (float)texData.width / context.GetWidth());
            vertices.push_back(ypos);
            vertices.push_back(texData.bottomRightU);
            vertices.push_back(texData.bottomRightV);

            indices.push_back(2 + index);
            indices.push_back(1 + index);
            indices.push_back(0 + index);

            indices.push_back(0 + index);
            indices.push_back(3 + index);
            indices.push_back(2 + index);

            index += 4;
            xpos += 2.f * (float)charInfo.xOffset / (float)context.GetWidth();
            ypos = oldy;
        }

        m_vao.SetVertexData(vertices);
        m_vao.SetIndexData(indices);
    }
}
