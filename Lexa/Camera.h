#pragma once
#include <memory>

#include "glm/glm.hpp"
#include "WindowEventManager.h"
#include "Window.h"

namespace Lexa
{
	class Camera
	{
	public:
		Camera(const std::shared_ptr<Window>& window);

		const glm::mat4& GetProjection() const;

		const glm::mat4& GetView() const;

		glm::vec3 GetDirection() const;

		void SetCenterOfRotation(const glm::vec3& vec);

		void SetContext(const std::shared_ptr<Window>& window);

	private:
		void UpdateZoom(double dz);

		void UpdatePosition();

		void UpdateProjectionMatrix(int width, int height);

		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::vec3 m_cameraPos;
		glm::vec3 m_cameraTarget;
		glm::vec3 m_cameraZ;
		glm::vec3 m_cameraX;
		glm::vec3 m_cameraY;

		struct OnScroll : public ScrollCallback
		{
			OnScroll(Camera& camera);
			void Execute(double dx, double dy) override;
			Camera& m_parent;
		};
		std::shared_ptr<ScrollCallback> m_onScroll;

		struct OnWindowRefresh : public FrameCallback
		{
			OnWindowRefresh(Camera& camera);
			void Execute() override;
			Camera& m_parent;
		};
		std::shared_ptr<FrameCallback> m_onWindowRefresh;

		struct OnWindowResize : public WindowResizeCallback
		{
			OnWindowResize(Camera& camera);
			void Execute(int width, int height) override;
			Camera& m_parent;
		};
		std::shared_ptr<WindowResizeCallback> m_onWindowResize;

		std::weak_ptr<Window> m_context;
	};
}

