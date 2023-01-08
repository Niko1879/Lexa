#include <glm/gtc/matrix_transform.hpp>

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
		float thetaX = glm::radians(-x);
		float thetaY = glm::radians(-y);
		glm::mat4 id(1.0f);
		id = glm::rotate(id, thetaY, m_cameraX);
		id = glm::rotate(id, thetaX, m_cameraY);

		glm::vec4 cameraXNew = id * glm::vec4(m_cameraX, 1.0f);
		glm::vec4 cameraYNew = id * glm::vec4(m_cameraY, 1.0f);
		glm::vec4 cameraZNew = id * glm::vec4(m_cameraZ, 1.0f);
		glm::vec4 cameraPosNew = id * glm::vec4(m_cameraPos, 1.0f);

		m_cameraX = glm::normalize(glm::vec3(cameraXNew.x, cameraXNew.y, cameraXNew.z));
		m_cameraY = glm::normalize(glm::vec3(cameraYNew.x, cameraYNew.y, cameraYNew.z));
		m_cameraZ = glm::normalize(glm::vec3(cameraZNew.x, cameraZNew.y, cameraZNew.z));
		m_cameraPos = glm::vec3(cameraPosNew.x, cameraPosNew.y, cameraPosNew.z);

		m_view = glm::lookAt(m_cameraPos, m_cameraTarget, m_cameraY);
	}


	void Camera::SetProjection(int width, int height)
	{
		m_projection = glm::perspective(glm::radians(45.0f), ((float)width) / height, 0.1f, 100.0f);
	}
}
