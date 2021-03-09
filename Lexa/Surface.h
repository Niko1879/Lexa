#pragma once
#include "SurfaceRenderData.h"
#include "Eval.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>



namespace Lexa
{
	class Surface
	{
	public:
		Surface(Interpreter::Eval2D&& eval, float xmin, float xmax, float ymin, float ymax, float step);

		void Resize(float xmin, float xmax, float ymin, float ymax, float step);

		void Draw(const glm::mat4& view, const glm::mat4& proj, const glm::vec3& cameraDirection);

		const glm::vec3& GetCentroid() const;

	private:
		void Generate();
		Interpreter::Eval2D eval;
		SurfaceRenderData renderData;
		float xmin, xmax, ymin, ymax;
		float step;
		glm::vec3 centroid;
	};
}
