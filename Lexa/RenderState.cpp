#include "RenderState.h"


namespace Lexa
{
	RenderState& RenderState::Instance()
	{
		static RenderState renderState;
		return renderState;
	}


	RenderState::RenderState()
	{

	}


	const std::weak_ptr<const VertexBuffer>& RenderState::GetVertexBuffer() const
	{
		return m_vertexBuffer;
	}


	const std::weak_ptr<Shader>& RenderState::GetShader() const
	{
		return m_shader;
	}


	const std::weak_ptr<RenderTarget>& RenderState::GetRenderTarget() const
	{
		return m_renderTarget;
	}


	const std::weak_ptr<Texture>& RenderState::GetTexture() const
	{
		return m_texture;
	}


	void RenderState::SetVertexBuffer(std::shared_ptr<const VertexBuffer> vertexBuffer)
	{
		m_vertexBuffer = std::weak_ptr(vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer ? vertexBuffer->m_bufs[0] : 0);
		glBindVertexArray(vertexBuffer ? *vertexBuffer->m_vao : 0);
	}


	void RenderState::SetShader(const std::shared_ptr<Shader>& shader)
	{
		m_shader = std::weak_ptr(shader);
		glUseProgram(*shader->m_id);
	}


	void RenderState::SetRenderTarget(const std::shared_ptr<RenderTarget>& renderTarget)
	{
		m_renderTarget = std::weak_ptr(renderTarget);
		glBindFramebuffer(GL_FRAMEBUFFER, *renderTarget->m_frameBuffer);
	}


	void RenderState::SetTexture(const std::shared_ptr<Texture>& texture)
	{
		m_texture = std::weak_ptr(texture);
		glBindTexture(GL_TEXTURE_2D, *texture->m_id);
	}


	void RenderState::Draw()
	{
		RenderState& renderState = RenderState::Instance();
		const std::weak_ptr<const VertexBuffer>& vb = renderState.GetVertexBuffer();

		if (!vb.expired())
		{
			std::shared_ptr<const VertexBuffer> vao = vb.lock();
			glDrawElements(GL_TRIANGLES, vao->GetSize(), GL_UNSIGNED_INT, 0);
		}
	}
}