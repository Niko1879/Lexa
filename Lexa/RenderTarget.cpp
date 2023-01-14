#include <glad/glad.h>

#include "RenderTarget.h"


namespace Lexa
{
	RenderTarget::RenderTarget() :
		m_frameBuffer(nullptr, [](GLuint* ptr) {glDeleteFramebuffers(1, ptr); delete ptr; })
	{
		InitFramebuffer();
	}


	void RenderTarget::SetTarget(const Texture& target) const
	{
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target.GetId(), 0);
	}


	void RenderTarget::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *m_frameBuffer);
	}


	void RenderTarget::InitFramebuffer()
	{
		GLuint frameBuffer;
		glGenFramebuffers(1, &frameBuffer);
		m_frameBuffer.reset(new GLuint(frameBuffer));
		glBindFramebuffer(GL_FRAMEBUFFER, *m_frameBuffer);
	}
}
