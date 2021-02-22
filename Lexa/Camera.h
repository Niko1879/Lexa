#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"


namespace Lexa
{
	namespace Camera
	{
		const glm::mat4& Projection();

		const glm::mat4& View();

		glm::vec3 Direction();

		void Init(float width, float height);

		void SetCenterOfRotation(const glm::vec3& vec);

		void OnWindowResize(float width, float height);

		void OnScroll(float dz);

		void OnDrag(float dx, float dy);


	}
}

