#pragma once

#include <memory>

#include "Texture.h"

namespace Lexa
{
	class RenderTarget
	{
		friend class RenderState;

	public:
		RenderTarget(int width, int height, Texture::Format format);

		RenderTarget(std::shared_ptr<Texture> tex);

		const std::shared_ptr<Texture>& GetTexture() const;

	private:
		void InitFramebuffer();

		std::unique_ptr<unsigned, void(*)(unsigned*)> m_frameBuffer;
		std::shared_ptr<Texture> m_renderTarget;
	};
}

