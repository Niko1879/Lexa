#pragma once

#include <unordered_map>

#include "Texture.h"
#include "RenderTarget.h"
#include "Shader.h"


namespace Lexa
{
	class TextureAtlas
	{
	public:
		TextureAtlas(std::unordered_map<std::string, std::shared_ptr<Texture>>& textures);

		struct TextureInfo
		{
			float width;
			float height;
			float bottomLeftU;
			float bottomLeftV;
			float bottomRightU;
			float bottomRightV;
			float topLeftU;
			float topLeftV;
			float topRightU;
			float topRightV;
		};

		const std::shared_ptr<Texture>& GetTexture() const;

		const TextureInfo& GetTexCoords(const std::string& name) const;

		int GetPerTexWidth() const;

		int GetperTextHeight() const;

	private:
		std::shared_ptr<Texture> Create(const std::unordered_map<std::string, std::shared_ptr<Texture>>& textures);

		TextureInfo GenTexCoord(float xpos, float ypos, float forwardxpos, float forwardypos);

		std::shared_ptr<Texture> m_tex;
		std::unordered_map<std::string, TextureInfo> m_texCoords;
		int m_perTexWidth;
		int m_perTexHeight;

		static const int MAX_TEX_WIDTH = 1024;
	};
}

