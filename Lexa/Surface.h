#pragma once
#include "Eval.h"
#include "glad/glad.h"


namespace Lexa
{
	class Surface
	{
	public:
		Surface(Interpreter::Eval2D&& eval, unsigned int shaderId);

		void Generate(float xmin, float xmax, float ymin, float ymax, float step);

		void Draw();

	private:
		Interpreter::Eval2D eval;
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		unsigned int shaderId;
	};
}

