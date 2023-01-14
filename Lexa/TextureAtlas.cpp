#include <algorithm> 

#include "VertexBuffer.h"
#include "RenderTarget.h"
#include "TextureAtlas.h"


namespace Lexa
{
	TextureAtlas::TextureAtlas(const std::unordered_map<std::string, Texture>& textures, const Shader& shader) 
        : m_tex(Create(textures))
	{
        static VertexBuffer vao(std::vector<int>{2, 2}, VertexBuffer::Format::DYNAMIC);
        RenderTarget rt;
        rt.SetTarget(m_tex);

        rt.Bind();
        shader.Bind();
        vao.Bind();

        static std::vector<unsigned> indices
        {
           3, 1, 0,
           0, 2, 3
        };
        vao.SetIndexData(indices);

        float xinc = 2.f * (float)m_perTexWidth / m_tex.GetWidth();
        float yinc = 2.f * (float)m_perTexHeight / m_tex.GetHeight();

        float xpos = -1.f;
        float ypos = -1.f;

        for (const std::pair<const std::string, Texture>& p : textures)
        {
            const std::string& name = p.first;
            const Texture& tex = p.second;

            tex.Bind();

            float forwardxpos = xpos + 2.f * tex.GetWidth() / m_tex.GetWidth();
            float forwardypos = ypos + 2.f * tex.GetHeight() / m_tex.GetHeight();

            m_texCoords[name] = GenTexCoord(xpos, ypos, forwardxpos, forwardypos, tex.GetWidth(), tex.GetHeight());

            std::vector<float> data
            {
                xpos, ypos, 0.f, 1.f,              
                xpos, forwardypos, 0.f, 0.f,      
                forwardxpos, ypos, 1.f, 1.f,      
                forwardxpos, forwardypos, 1.f, 0.f
            };

            vao.SetVertexData(data);
            glDrawElements(GL_TRIANGLES, vao.GetSize(), GL_UNSIGNED_INT, 0);

            xpos += xinc;
            if (xpos > 1.f)
            {
                xpos = -1.f;
                ypos += yinc;
            }
        }
	}


    const Texture& TextureAtlas::GetTexture() const
    {
        return m_tex;
    }


    const TextureAtlas::TextureInfo& TextureAtlas::GetTextureData(const std::string& name) const
    {
        return m_texCoords.at(name);
    }


    int TextureAtlas::GetPerTexWidth() const
    {
        return m_perTexWidth;
    }

    int TextureAtlas::GetperTextHeight() const
    {
        return m_perTexHeight;
    }


    Texture TextureAtlas::Create(const std::unordered_map<std::string, Texture>& textures)
    {
        m_perTexWidth = std::max_element
        (
            textures.begin(), 
            textures.end(), 
            []
            (
                const std::pair<const std::string, Texture>& l, const std::pair<const std::string, Texture>& r)
                {
                    return l.second.GetWidth() < r.second.GetWidth(); 
                }
            )
            ->second.GetWidth();
        
        m_perTexHeight = std::max_element
        (
            textures.begin(), 
            textures.end(), 
            []
            (
                const std::pair<const std::string, Texture>& l, const std::pair<const std::string, Texture>& r)
                {
                    return l.second.GetHeight() < r.second.GetHeight(); 
                }
        )
        ->second.GetHeight();

        int ntex = textures.size();

        int renderTargetWidth = pow(2, (ceil(log2(m_perTexWidth * ntex))));
        int renderTargetHeight = pow(2, ceil(log2(m_perTexHeight)));

        while (renderTargetWidth > MAX_TEX_WIDTH)
        {
            renderTargetWidth /= 2;
            renderTargetHeight *= 2;
        }

        return Texture(renderTargetWidth, renderTargetHeight, Texture::Format::RGBA);
    }


    TextureAtlas::TextureInfo TextureAtlas::GenTexCoord(float xpos, float ypos, float forwardxpos, float forwardypos, int width, int height)
    {
        auto f = [](float x) {return (x + 1.f) / 2.f; };

        xpos = f(xpos);
        ypos = f(ypos);
        forwardxpos = f(forwardxpos);
        forwardypos = f(forwardypos);

        return TextureInfo{width, height, xpos, ypos, forwardxpos, ypos, xpos, forwardypos, forwardxpos, forwardypos };
    }
}
