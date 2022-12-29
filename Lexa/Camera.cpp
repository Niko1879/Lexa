#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "GLFW/glfw3.h"


namespace Lexa
{
	Camera::Camera(const std::shared_ptr<Window>& window) :
		m_projection(1.0f),
		m_view(1.0f),
		m_cameraPos(0.0f, 0.0f, 0.0f),
		m_cameraTarget(0.0f, 0.0f, 0.0f),
		m_cameraZ(0.0f, 0.0f, 1.0f),
		m_cameraX(1.0f, 0.0f, 0.0f),
		m_cameraY(0.0f, 1.0f, 0.0f),
		m_context(window),
		m_onScroll(new OnScroll(*this)),
		m_onWindowRefresh(new OnWindowRefresh(*this)),
		m_onWindowResize(new OnWindowResize(*this))
	{
		SetContext(window);
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


	void Camera::SetContext(const std::shared_ptr<Window>& window)
	{
		UpdateProjectionMatrix(window->GetWidth(), window->GetHeight());
		UpdateZoom(-3.f);

		window->AddScrollCallback(m_onScroll);
		window->AddFrameCallback(m_onWindowRefresh);
		window->AddWindowResizeCallback(m_onWindowResize);

		m_context = window;
	}


	Camera::OnScroll::OnScroll(Camera& camera) : m_parent(camera) {}


	void Camera::OnScroll::Execute(double dx, double dy)
	{
		m_parent.UpdateZoom(dy);
	}


	Camera::OnWindowRefresh::OnWindowRefresh(Camera& camera) : m_parent(camera) {}


	void Camera::OnWindowRefresh::Execute()
	{
		if (m_parent.m_context.lock()->GetMouseDown())
		{
			m_parent.UpdatePosition();
		}
	}


	Camera::OnWindowResize::OnWindowResize(Camera& camera) : m_parent(camera) {}


	void Camera::OnWindowResize::Execute(int width, int height)
	{
		m_parent.UpdateProjectionMatrix(width, height);
	}


	void Camera::UpdateZoom(double dz)
	{
		glm::vec3 inc = (float)dz * m_cameraZ;
		m_cameraPos -= inc;
		m_view = glm::translate(m_view, inc);
	}


	void Camera::UpdatePosition()
	{
		std::pair<float, float> cursordelta = m_context.lock()->GetCursorDelta();
		float dx = cursordelta.first;
		float dy = cursordelta.second;

		float thetaX = glm::radians(-dx);
		float thetaY = glm::radians(-dy);
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


	void Camera::UpdateProjectionMatrix(int width, int height)
	{
		m_projection = glm::perspective(glm::radians(45.0f), ((float)width) / height, 0.1f, 100.0f);
	}
}