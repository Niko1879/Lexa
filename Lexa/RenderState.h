#pragma once
#include <memory>

#include "VertexBuffer.h"
#include "Shader.h"
#include "RenderTarget.h"
#include "Texture.h"


namespace Lexa
{
	class RenderState
	{
	public:
		static RenderState& Instance();

		void Draw();

	private:
		RenderState();

		RenderState(const RenderState& other) = delete;

		RenderState(RenderState&& other) = delete;

		RenderState& operator=(const RenderState& other) = delete;

		RenderState& operator=(RenderState&& other) = delete;
	};
}

