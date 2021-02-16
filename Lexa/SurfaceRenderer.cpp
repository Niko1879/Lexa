#include "SurfaceRenderer.h"

namespace Lexa
{
	SurfaceRenderer::SurfaceRenderer(Interpreter::Eval2D&& eval) : 
		eval(std::move(eval)),
		ymin(-1.0f),
		ymax(1.0f),
		xmin(-1.0f),
		xmax(1.0f),
		step(0.1f),
		mvp(1.0f)
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		shaderId = Shader::CreateShader("Surface.vs", "Surface.fs");
		glUseProgram(shaderId);
		mvpLoc = glGetUniformLocation(shaderId, "MVP");
	}

	void SurfaceRenderer::Generate()
	{
		vertices.clear();
		indices.clear();
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

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		size_t xCount = round((xmax - xmin) / step);
		size_t yCount = round((ymax - ymin) / step);
		++xCount;
		++yCount;

		for (size_t j = 0; j < yCount - 1; ++j)
		{
			for (size_t i = j; i <= vertices.size() / 3 - yCount - 1; i += yCount)
			{
				indices.push_back(i);
				indices.push_back(i + 1);
				indices.push_back(i + yCount);
				indices.push_back(i + yCount);
				indices.push_back(i + 1);
				indices.push_back(i + yCount + 1);
			}
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	void SurfaceRenderer::Rotate(float dx, float dy, float dz)
	{
		mvp = glm::rotate(mvp, dx, glm::vec3(1.0f, 0.0f, 0.0f));
		mvp = glm::rotate(mvp, dy, glm::vec3(0.0f, 1.0f, 0.0f));
		mvp = glm::rotate(mvp, dz, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void SurfaceRenderer::Draw()
	{
		glBindVertexArray(VAO);
		glUseProgram(shaderId);
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}