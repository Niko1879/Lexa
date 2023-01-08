#pragma once

#include <memory>

#include "Texture.h"


namespace Lexa
{
	class RenderTarget
	{
	public:
		RenderTarget();

		void SetTarget(const Texture& target) const;

		void Bind() const;

	private:
		void InitFramebuffer();

		std::unique_ptr<unsigned, void(*)(unsigned*)> m_frameBuffer;
	};
}

