#pragma once
#include "Eval.h"
#include "glad/glad.h"
#include <vector>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Lexa
{
	class SurfaceRenderer
	{
	public:
		SurfaceRenderer(Interpreter::Eval2D&& eval);

		void Generate();

		void Draw();

		void Rotate(float dx, float dy, float dz);

		float xmin, xmax, ymin, ymax, step;

	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		Interpreter::Eval2D eval;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		unsigned int shaderId;
		unsigned int mvpLoc;
		glm::mat4 mvp;
	};
}

