#include <glad/glad.h>

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


	void RenderState::Draw(unsigned count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}
}
