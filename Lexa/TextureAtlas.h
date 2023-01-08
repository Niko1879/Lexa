#pragma once

#include <unordered_map>

#include "Texture.h"
#include "Shader.h"


namespace Lexa
{
	class TextureAtlas
	{
	public:
		TextureAtlas(const std::unordered_map<std::string, Texture>& textures, const Shader& shader);

		struct TextureInfo
		{
			int width;
			int height;
			float bottomLeftU;
			float bottomLeftV;
			float bottomRightU;
			float bottomRightV;
			float topLeftU;
			float topLeftV;
			float topRightU;
			float topRightV;
		};

		const Texture& GetTexture() const;

		const TextureInfo& GetTextureData(const std::string& name) const;

		int GetPerTexWidth() const;

		int GetperTextHeight() const;

	private:
		Texture Create(const std::unordered_map<std::string, Texture>& textures);

		TextureInfo GenTexCoord(float xpos, float ypos, float forwardxpos, float forwardypos, int width, int height);

		Texture m_tex;
		std::unordered_map<std::string, TextureInfo> m_texCoords;
		int m_perTexWidth;
		int m_perTexHeight;

		static const int MAX_TEX_WIDTH = 1024;
	};
}
