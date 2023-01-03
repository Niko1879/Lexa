#include <glad/glad.h>
#include <algorithm> 

#include "VertexBuffer.h"
#include "TextureAtlas.h"
#include "RenderState.h"


namespace Lexa
{
	TextureAtlas::TextureAtlas(std::unordered_map<std::string, std::shared_ptr<Texture>>& textures) : m_tex(Create(textures))
	{
        std::shared_ptr<VertexBuffer> vao = std::make_shared<VertexBuffer>(std::vector<int>{2, 2}, VertexBuffer::Format::DYNAMIC);
        std::shared_ptr<RenderTarget> rt = std::make_shared<RenderTarget>(m_tex);
        std::shared_ptr<Shader> shader = std::make_shared<Shader>("Quad.vs", "Quad.fs");

        RenderState& rs = RenderState::Instance();

        std::weak_ptr<RenderTarget> oldRt = rs.GetRenderTarget();
        std::weak_ptr<Texture> oldTex = rs.GetTexture();
        std::weak_ptr<VertexBuffer> oldVao = rs.GetVertexBuffer();
        std::weak_ptr<Shader> oldShader = rs.GetShader();

        rs.SetVertexBuffer(vao);
        rs.SetRenderTarget(rt);
        rs.SetShader(shader);

        std::vector<unsigned> indices
        {
           3, 1, 0,
           0, 2, 3
        };
        vao->AddIndices(indices);

        float xinc = 2.f * (float)m_perTexWidth / m_tex->GetWidth();
        float yinc = 2.f * (float)m_perTexHeight / m_tex->GetHeight();

        float xpos = -1.f;
        float ypos = -1.f;

        for (std::pair<const std::string, std::shared_ptr<Texture>>& p : textures)
        {
            const std::string& name = p.first;
            std::shared_ptr<Texture>& tex = p.second;

            rs.SetTexture(tex);

            float forwardxpos = xpos + 2.f * tex->GetWidth() / m_tex->GetWidth();
            float forwardypos = ypos + 2.f * tex->GetHeight() / m_tex->GetHeight();

            m_texCoords[name] = GenTexCoord(xpos, ypos, forwardxpos, forwardypos);

            std::vector<float> data
            {
                xpos, ypos, 0.f, 1.f,              
                xpos, forwardypos, 0.f, 0.f,      
                forwardxpos, ypos, 1.f, 1.f,      
                forwardxpos, forwardypos, 1.f, 0.f
            };

            vao->AddData(data);
            rs.Draw();

            xpos += xinc;
            if (xpos > 1.f)
            {
                xpos = -1.f;
                ypos += yinc;
            }
        }

        if (!oldRt.expired())
            rs.SetRenderTarget(oldRt.lock());
        if (!oldShader.expired())
            rs.SetShader(oldShader.lock());
        if (!oldTex.expired())
            rs.SetTexture(oldTex.lock());
        if (!oldVao.expired())
            rs.SetVertexBuffer(oldVao.lock());
	}


    const std::shared_ptr<Texture>& TextureAtlas::GetTexture() const
    {
        return m_tex;
    }


    const TextureAtlas::TextureInfo& TextureAtlas::GetTexCoords(const std::string& name) const
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


    std::shared_ptr<Texture> TextureAtlas::Create(const std::unordered_map<std::string, std::shared_ptr<Texture>>& textures)
    {
        m_perTexWidth = std::max_element
        (
            textures.begin(), 
            textures.end(), 
            []
            (
                const std::pair<const std::string, std::shared_ptr<Texture>>& l, const std::pair<std::string, std::shared_ptr<Texture>>& r)
                {
                    return l.second->GetWidth() < r.second->GetWidth(); 
                }
            )
            ->second->GetWidth();
        
        m_perTexHeight = std::max_element
        (
            textures.begin(), 
            textures.end(), 
            []
            (
                const std::pair<const std::string, std::shared_ptr<Texture>>& l, const std::pair<std::string, std::shared_ptr<Texture>>& r)
                {
                    return l.second->GetHeight() < r.second->GetHeight(); 
                }
        )
        ->second->GetHeight();

        int ntex = textures.size();

        int renderTargetWidth = pow(2, (ceil(log2(m_perTexWidth * ntex))));
        int renderTargetHeight = pow(2, ceil(log2(m_perTexHeight)));

        while (renderTargetWidth > MAX_TEX_WIDTH)
        {
            renderTargetWidth /= 2;
            renderTargetHeight *= 2;
        }

        return std::make_shared<Texture>(renderTargetWidth, renderTargetHeight, Texture::Format::RGBA);
    }


    TextureAtlas::TextureInfo TextureAtlas::GenTexCoord(float xpos, float ypos, float forwardxpos, float forwardypos)
    {
        auto f = [](float x) {return (x + 1.f) / 2.f; };

        xpos = f(xpos);
        ypos = f(ypos);
        forwardxpos = f(forwardxpos);
        forwardypos = f(forwardypos);

        float width = forwardxpos - xpos;
        float height = forwardypos - ypos;

        return TextureInfo{width, height, xpos, ypos, forwardxpos, ypos, xpos, forwardypos, forwardxpos, forwardypos };
    }
}