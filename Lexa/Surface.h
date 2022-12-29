#pragma once
#include "Eval.h"
#include "glm/glm.hpp"
#include "VertexBuffer.h"


namespace Lexa
{
	class Surface
	{
	public:
		Surface(Interpreter::Eval2D&& eval, float xmin, float xmax, float ymin, float ymax, float step);

		void Resize(float xmin, float xmax, float ymin, float ymax, float step);

		const glm::vec3& GetCentroid() const;

	private:
		void Generate();
		
		VertexBuffer m_vao;
		unsigned m_indexCount;
		
		Interpreter::Eval2D m_eval;
		float m_xmin, m_xmax, m_ymin, m_ymax;
		float m_step;
		glm::vec3 m_centroid;
	};
}
