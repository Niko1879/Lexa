#pragma once
#include <vector>
#include <memory>


namespace Lexa
{
	class Texture
	{
		friend class RenderTarget;
		friend class RenderState;

	public:
		enum class Format
		{
			RED,
			RGBA
		};


		Texture(int width, int height, Format format, const std::vector<uint8_t>& data);
		
		Texture(int width, int height, Format format);

		unsigned GetId() const;

		int GetWidth() const;

		int GetHeight() const;

	private:
		std::unique_ptr<unsigned, void(*)(unsigned*)> m_id;
		unsigned m_width;
		unsigned m_height;
	};
}

