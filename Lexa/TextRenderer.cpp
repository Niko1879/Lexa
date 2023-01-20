#include <algorithm>

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
        m_vao.Bind();
        const std::string& text = textbox.GetText();
        const std::string& fontStr = textbox.GetFont();
        int fontSize = textbox.GetFontSize();
        const Font& font = textManager.GetFont(fontStr, fontSize);

        std::pair<int, int> pos = textbox.GetPosition();
        float scrWidth = context.GetWidth();
        float scrHeight = context.GetHeight();
        float xpos = 2.f * pos.first / scrWidth - 1.f;
        float ypos = 2.f * pos.second / scrHeight - 1.f;
        float scale = textbox.GetFontScale();

        std::vector<float> vertices;
        std::vector<unsigned> indices;
        int index = 0;

        float yBearing = scale * 2.f * 
            std::max_element(font.charInfo.begin(), font.charInfo.end(), [](const std::pair<std::string, CharInfo>& a, const std::pair<std::string, CharInfo>& b)
            {
                return a.second.yOffset < b.second.yOffset;
            })
            ->second.yOffset / scrHeight;

        for (char c : text)
        {
            std::string ch(1, c);

            TextureAtlas::TextureInfo texData = font.textureAtlas.GetTextureData(ch);
            const CharInfo& charInfo = font.charInfo.at(ch);

            float yoffset = scale * 2.f * charInfo.yOffset / scrHeight;
            float oldy = ypos;
            ypos = ypos - yoffset + yBearing;

            float forwardXpos = xpos + scale * 2.f * texData.width / scrWidth;
            float forwardYpos = ypos + scale * 2.f * texData.height / scrHeight;

            //bottomleft
            vertices.push_back(xpos);
            vertices.push_back(ypos);
            vertices.push_back(texData.bottomLeftU);
            vertices.push_back(texData.bottomLeftV);

            //topleft
            vertices.push_back(xpos);
            vertices.push_back(forwardYpos);
            vertices.push_back(texData.topLeftU);
            vertices.push_back(texData.topLeftV);

            //topright
            vertices.push_back(forwardXpos);
            vertices.push_back(forwardYpos);
            vertices.push_back(texData.topRightU);
            vertices.push_back(texData.topRightV);

            //bottomright
            vertices.push_back(forwardXpos);
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
            xpos += scale * 2.f * charInfo.xOffset / scrWidth;
            ypos = oldy;
        }

        m_vao.SetVertexData(vertices);
        m_vao.SetIndexData(indices);
    }
}
