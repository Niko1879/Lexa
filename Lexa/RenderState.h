#pragma once


namespace Lexa
{
	class RenderState
	{
	public:
		static RenderState& Instance();

		void Draw(unsigned count);

	private:
		RenderState();

		RenderState(const RenderState& other) = delete;

		RenderState(RenderState&& other) = delete;

		RenderState& operator=(const RenderState& other) = delete;

		RenderState& operator=(RenderState&& other) = delete;
	};
}
