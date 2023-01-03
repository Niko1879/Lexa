#pragma once
#include <memory>

#include "glm/glm.hpp"


namespace Lexa
{
	class Camera
	{
	public:
		Camera();

		const glm::mat4& GetProjection() const;

		const glm::mat4& GetView() const;

		glm::vec3 GetDirection() const;

		void SetCenterOfRotation(const glm::vec3& vec);

		void Update(int scrWidth, int scrHeight, float cursorDeltaX, float cursorDeltaY, float scrollDelta);

	private:
		void UpdateZoom(double dz);

		void UpdatePosition(float dx, float dy);

		void UpdateProjectionMatrix(int width, int height);

		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::vec3 m_cameraPos;
		glm::vec3 m_cameraTarget;
		glm::vec3 m_cameraZ;
		glm::vec3 m_cameraX;
		glm::vec3 m_cameraY;
	};
}

