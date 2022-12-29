#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Texture.h"
#include "TextureAtlas.h"


namespace Lexa
{
	class TextManager
	{
	public:
		TextManager();

		void AddFont(const std::string& name, const std::string& path, unsigned size);

		const TextureAtlas& GetFont(const std::string& font, unsigned size) const;

	private:
		std::unordered_map<unsigned, std::unordered_map<std::string, TextureAtlas>> m_fonts;
		static std::unique_ptr<std::remove_pointer<FT_Library>::type, void(*)(FT_Library)> s_FtLibrary;
	};
}

