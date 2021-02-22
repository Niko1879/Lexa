#include "Camera.h"

namespace Lexa
{
	namespace Camera
	{
		glm::mat4 projection(1.0f);
		glm::mat4 view(1.0f);
		glm::vec3 cameraPos(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraZ(0.0f, 0.0f, 1.0f);
		glm::vec3 cameraX(1.0f, 0.0f, 0.0f);
		glm::vec3 cameraY(0.0f, 1.0f, 0.0f);

		const glm::mat4& Projection()
		{
			return projection;
		}

		const glm::mat4& View()
		{
			return view;
		}

		glm::vec3 Direction()
		{
			return glm::normalize(cameraPos - cameraTarget);
		}

		void Init(float width, float height)
		{
			OnWindowResize(width, height);
			OnScroll(-3.0f);
		}

		void SetCenterOfRotation(const glm::vec3& vec)
		{
			cameraTarget = vec;
		}

		void OnWindowResize(float width, float height)
		{
			projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
		}

		void OnScroll(float dz)
		{
			glm::vec3 inc = dz * cameraZ;
			cameraPos -= inc;
			view = glm::translate(view, inc);

		}

		void OnDrag(float dx, float dy)
		{
			float thetaX = glm::radians(-dx);
			float thetaY = glm::radians(-dy);
			glm::mat4 id(1.0f);
			id = glm::rotate(id, thetaY, cameraX);
			id = glm::rotate(id, thetaX, cameraY);

			glm::vec4 cameraX_ = id * glm::vec4(cameraX, 1.0f);
			glm::vec4 cameraY_ = id * glm::vec4(cameraY, 1.0f);
			glm::vec4 cameraZ_ = id * glm::vec4(cameraZ, 1.0f);
			glm::vec4 cameraPos_ = id * glm::vec4(cameraPos, 1.0f);

			cameraX = glm::normalize(glm::vec3(cameraX_.x, cameraX_.y, cameraX_.z));
			cameraY = glm::normalize(glm::vec3(cameraY_.x, cameraY_.y, cameraY_.z));
			cameraZ = glm::normalize(glm::vec3(cameraZ_.x, cameraZ_.y, cameraZ_.z));
			cameraPos = glm::vec3(cameraPos_.x, cameraPos_.y, cameraPos_.z);

			view = glm::lookAt(cameraPos, cameraTarget, cameraY);
		}
	}
}