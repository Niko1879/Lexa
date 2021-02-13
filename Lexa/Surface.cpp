#include "Surface.h"


namespace Lexa
{
	Surface::Surface(Interpreter::Eval2D&& eval, unsigned int shaderId) : eval(std::move(eval)), shaderId(shaderId)
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void Surface::Generate(float xmin, float xmax, float ymin, float ymax, float step)
	{
		vertices.clear();
		float tolerance = step / 10.0f;
		for (float x = xmin; x < xmax + tolerance; x += step)
		{
			for (float y = ymin; y < ymax + tolerance; y += step)
			{
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(eval(x, y));
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		size_t xNum = round(xmax - xmin) / step;
		size_t yNum = round(ymax - ymin) / step;
		++xNum;
		++yNum;

		size_t numVertices = vertices.size() / 3;

		for (size_t start = 0; start < yNum - 1; ++start)
		{
			for (size_t i = start; i <= numVertices - yNum - 1; i += yNum)
			{
				indices.push_back(i);
				indices.push_back(i + 1);
				indices.push_back(i + yNum);
				indices.push_back(i + 1);
				indices.push_back(i + yNum + 1);
				indices.push_back(i + yNum);
			}
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	void Surface::Draw()
	{
		glUseProgram(shaderId);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}