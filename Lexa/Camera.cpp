#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Camera.h"
#include "GLFW/glfw3.h"


namespace Lexa
{
	Camera::Camera() :
		m_projection(1.0f),
		m_view(1.0f),
		m_cameraPos(0.0f, 0.0f, 0.0f),
		m_cameraTarget(0.0f, 0.0f, 0.0f),
		m_cameraZ(0.0f, 0.0f, 1.0f),
		m_cameraX(1.0f, 0.0f, 0.0f),
		m_cameraY(0.0f, 1.0f, 0.0f)
	{

	}


	const glm::mat4& Camera::GetProjection() const
	{
		return m_projection;
	}


	const glm::mat4& Camera::GetView() const
	{
		return m_view;
	}


	glm::vec3 Camera::GetDirection() const
	{
		return glm::normalize(m_cameraPos - m_cameraTarget);
	}


	void Camera::SetCenterOfRotation(const glm::vec3& vec)
	{
		m_cameraTarget = vec;
	}


	void Camera::Zoom(float dz)
	{
		glm::vec3 inc = dz * m_cameraZ;
		m_cameraPos -= inc;
		m_view = glm::translate(m_view, inc);
	}


	void Camera::Rotate(float x, float y)
	{
		static glm::quat rotation(1.f, 0.f, 0.f, 0.f);
		rotation = glm::angleAxis(0.06f, glm::normalize(glm::vec3(-y, -x, 0.f))) * rotation;
		m_view = glm::lookAt(rotation * m_cameraPos, m_cameraTarget, rotation * m_cameraY);
	}


	void Camera::SetProjection(int width, int height)
	{
		m_projection = glm::perspective(glm::radians(45.0f), ((float)width) / height, 0.1f, 100.0f);
	}
}
