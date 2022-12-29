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

		const std::weak_ptr<VertexBuffer>& GetVertexBuffer() const;

		const std::weak_ptr<Shader>& GetShader() const;

		const std::weak_ptr<RenderTarget>& GetRenderTarget() const;

		const std::weak_ptr<Texture>& GetTexture() const;

		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

		void SetShader(const std::shared_ptr<Shader>& shader);

		void SetRenderTarget(const std::shared_ptr<RenderTarget>& renderTarget);

		void SetTexture(const std::shared_ptr<Texture>& texture);

		void Draw() const;

	private:
		RenderState();

		RenderState(const RenderState& other) = delete;

		RenderState(RenderState&& other) = delete;

		RenderState& operator=(const RenderState& other) = delete;

		RenderState& operator=(RenderState&& other) = delete;

		std::weak_ptr<VertexBuffer> m_vertexBuffer;
		std::weak_ptr<Shader> m_shader;
		std::weak_ptr<RenderTarget> m_renderTarget;
		std::weak_ptr<Texture> m_texture;
	};
}

