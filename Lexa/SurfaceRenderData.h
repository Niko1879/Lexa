#pragma once
#include "glad/glad.h"
#include <vector>
#include "Shader.h"
#include "glm/glm.hpp"


namespace Lexa
{
	struct SurfaceRenderData
	{
		SurfaceRenderData() : model(1.0f)
		{
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			shaderId = Shader::CreateShader("Surface.vs", "Surface.fs");
			glUseProgram(shaderId);
			modelLoc = glGetUniformLocation(shaderId, "model");
			viewLoc = glGetUniformLocation(shaderId, "view");
			projLoc = glGetUniformLocation(shaderId, "projection");
			cameraDirectionLoc = glGetUniformLocation(shaderId, "cameraDirection");
		}

		const int numAttrib = 6;
		std::vector<float> vertices;
		std::vector<GLuint> indices;
		GLuint VBO;
		GLuint VAO;
		GLuint EBO;
		GLuint shaderId;
		GLuint modelLoc, viewLoc, projLoc, cameraDirectionLoc;
		glm::mat4 model;
	};
}

