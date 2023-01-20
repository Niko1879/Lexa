#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


namespace Lexa
{
	class Camera
	{
	public:
		Camera();

		const glm::mat4& GetProjection() const;

		glm::mat4 GetView() const;

		glm::vec3 GetDirection() const;

		void SetProjection(int width, int height);

		void SetCenterOfRotation(const glm::vec3& vec);

		void SetSpeed(float speed);

		void SetZoomSpeed(float speed);
		
		void SetZoomLimit(float limit);
		
		void Rotate(float x, float y);

		void Zoom(float amount);

	private:
		glm::mat4 m_projection;
		glm::vec3 m_cameraPos;
		glm::vec3 m_cameraTarget;
		glm::vec3 m_cameraUp;
		glm::quat m_rotation;
		float m_zoomLimit;
		float m_speed;
		float m_zoomSpeed;
	};
}
