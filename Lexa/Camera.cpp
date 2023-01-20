#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "GLFW/glfw3.h"


namespace Lexa
{
	Camera::Camera() :
		m_projection(1.0f),
		m_cameraPos(0.0f, 0.0f, 10.f),
		m_cameraTarget(0.0f, 0.0f, 0.0f),
		m_cameraUp(0.0f, 1.0f, 0.0f),
		m_rotation(1.f, 0.f, 0.f, 0.f),
		m_zoomLimit(3.f),
		m_speed(0.1f),
		m_zoomSpeed(1.f)
	{

	}


	const glm::mat4& Camera::GetProjection() const
	{
		return m_projection;
	}


	glm::mat4 Camera::GetView() const
	{
		return glm::lookAt(m_rotation * m_cameraPos, m_cameraTarget, m_rotation * m_cameraUp);
	}


	glm::vec3 Camera::GetDirection() const
	{
		return glm::normalize(m_rotation * m_cameraPos - m_cameraTarget);
	}


	void Camera::SetCenterOfRotation(const glm::vec3& vec)
	{
		m_cameraTarget = vec;
	}


	void Camera::SetSpeed(float speed)
	{
		m_speed = speed;
	}


	void Camera::SetZoomSpeed(float speed)
	{
		m_zoomSpeed = speed;
	}


	void Camera::SetZoomLimit(float limit)
	{
		m_zoomLimit = limit;
	}


	void Camera::Zoom(float amount)
	{
		if (m_cameraPos.z - m_zoomSpeed * amount > m_zoomLimit)
		{
			m_cameraPos.z = m_cameraPos.z - m_zoomSpeed * amount;
		}
	}


	void Camera::Rotate(float x, float y)
	{
		m_rotation = m_rotation * glm::angleAxis(m_speed, glm::normalize(glm::vec3(y, -x, 0.f)));
	}


	void Camera::SetProjection(int width, int height)
	{
		m_projection = glm::perspective(glm::radians(45.0f), ((float)width) / height, 0.1f, 100.0f);
	}
}
