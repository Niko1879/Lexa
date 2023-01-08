#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "TextManager.h"
#include "VertexBuffer.h"


namespace Lexa
{
    std::unique_ptr<std::remove_pointer<FT_Library>::type, void(*)(FT_Library)> TextManager::s_FtLibrary(nullptr, [](FT_Library ptr) {FT_Done_FreeType(ptr); });


    TextManager::TextManager()
    {
        if (!s_FtLibrary)
        {
            FT_Library ft;
            FT_Init_FreeType(&ft);
            s_FtLibrary.reset(ft);
        }
    }


	void TextManager::AddFont(const std::string& name, const std::string& path, unsigned size, const Shader& shader)
	{
        FT_Face _face;
        FT_New_Face(s_FtLibrary.get(), path.c_str(), 0, &_face);
        std::unique_ptr<std::remove_pointer<FT_Face>::type, void(*)(FT_Face)> face(_face, [](FT_Face ptr) {FT_Done_Face(ptr); });

        FT_Set_Pixel_Sizes(face.get(), 0, size);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        std::unordered_map<std::string, Texture> characters;

        for (unsigned char c = 0; c < 128; c++)
        {
            FT_Load_Char(face.get(), c, FT_LOAD_RENDER);

            std::vector<uint8_t> data;
            int width = face->glyph->bitmap.width;
            int height = face->glyph->bitmap.rows;
            uint8_t* _raw = face->glyph->bitmap.buffer;
            for (int i = 0; i < width * height; ++i)
            {
                data.push_back(0);
                data.push_back(0);
                data.push_back(0);
                data.push_back(_raw[i]);
            }

            std::string ch(1, c);
            characters.emplace
            (
                std::piecewise_construct,
                std::forward_as_tuple(ch),
                std::forward_as_tuple(width, height, Texture::Format::RGBA, data)
            );

            m_charInfo[size][name][ch] = CharInfo{face->glyph->advance.x >> 6, height - face->glyph->bitmap_top};
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        m_fonts[size].emplace
        (
            std::piecewise_construct,
            std::forward_as_tuple(name),
            std::forward_as_tuple(characters, shader)
        );
	}


    const TextureAtlas& TextManager::GetFont(const std::string& font, unsigned size) const
    {
        return m_fonts.at(size).at(font);
    }


    const TextManager::CharInfo& TextManager::GetCharInfo(const std::string& font, unsigned size, const std::string& c) const
    {
        return m_charInfo.at(size).at(font).at(c);
    }
}
