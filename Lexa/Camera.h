#pragma once

#include <memory>
#include <glm/glm.hpp>


namespace Lexa
{
	class Camera
	{
	public:
		Camera();

		const glm::mat4& GetProjection() const;

		const glm::mat4& GetView() const;

		glm::vec3 GetDirection() const;

		void SetProjection(int width, int height);

		void SetCenterOfRotation(const glm::vec3& vec);

		void Rotate(float x, float y);

		void Zoom(float z);

	private:
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::vec3 m_cameraPos;
		glm::vec3 m_cameraTarget;
		glm::vec3 m_cameraZ;
		glm::vec3 m_cameraX;
		glm::vec3 m_cameraY;
	};
}
