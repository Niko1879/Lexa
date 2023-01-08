#include <glad/glad.h>

#include "RenderTarget.h"
#include "RenderState.h"


namespace Lexa
{
	RenderTarget::RenderTarget(int width, int height, Texture::Format format) :
		m_frameBuffer(nullptr, [](GLuint* ptr) {glDeleteFramebuffers(1, ptr); delete ptr; }),
		m_renderTarget(std::make_shared<Texture>(width, height, format))
	{
		InitFramebuffer();
	}

	RenderTarget::RenderTarget(std::shared_ptr<Texture> tex) :
		m_frameBuffer(nullptr, [](GLuint* ptr) {glDeleteFramebuffers(1, ptr); }),
		m_renderTarget(tex)
	{
		InitFramebuffer();
	}


	void RenderTarget::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *m_frameBuffer);
	}


	const std::shared_ptr<Texture>& RenderTarget::GetTexture() const
	{
		return m_renderTarget;
	}


	void RenderTarget::InitFramebuffer()
	{
		GLuint frameBuffer;
		glGenFramebuffers(1, &frameBuffer);
		m_frameBuffer.reset(new GLuint(frameBuffer));
		glBindFramebuffer(GL_FRAMEBUFFER, *m_frameBuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *m_renderTarget->m_id, 0);
	}
}