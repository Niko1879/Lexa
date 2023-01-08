#include <unordered_map>
#include <glad/glad.h>

#include "Texture.h"
#include "RenderState.h"


namespace Lexa
{
    const static std::unordered_map<Texture::Format, GLint> s_Format
    {
        {Texture::Format::RED, GL_RED},
        {Texture::Format::RGBA, GL_RGBA},
    };


    Texture::Texture(int width, int height, Format format, const std::vector<uint8_t>& data) : 
        m_id(nullptr, [](GLuint* ptr) {glDeleteTextures(1, ptr); delete ptr; }),
        m_width(width),
        m_height(height)
	{
        GLint glFormat = s_Format.at(format);

        // TODO (if necessary): Generalise to other texture formats
        GLuint id;
        glGenTextures(1, &id);
        m_id.reset(new GLuint(id));
        
        glBindTexture(GL_TEXTURE_2D, *m_id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data.data());
        glGenerateMipmap(GL_TEXTURE_2D);
	}


    Texture::Texture(int width, int height, Format format) : Texture(width, height, format, std::vector<uint8_t>())
    {

    }



    unsigned Texture::GetId() const
    {
        return *m_id;
    }


    int Texture::GetWidth() const
    {
        return m_width;
    }


    int Texture::GetHeight() const
    {
        return m_height;
    }


    void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, *m_id);
    }
}