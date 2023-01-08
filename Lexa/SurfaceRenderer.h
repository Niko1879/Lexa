#pragma once

#include <glm/glm.hpp>

#include "Eval.h"
#include "VertexBuffer.h"


namespace Lexa
{
	class SurfaceRenderer
	{
	public:
		SurfaceRenderer();

		void Generate(const Interpreter::Eval2D& eval, float xmin, float xmax, float ymin, float ymax, float step);

		const VertexBuffer& GetGeometry() const;

		const glm::vec3& GetCentroid() const;

	private:
		VertexBuffer m_vao;
		glm::vec3 m_centroid;
	};
}
