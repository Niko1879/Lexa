#pragma once

#include <string>
#include <memory>

#include "IO.h"
#include "glm/glm.hpp"


namespace Lexa
{
	class Shader
	{
		friend class RenderState;

	public:
		Shader(const std::string& vertexSrc, const std::string& fragSrc);

		unsigned GetId() const;

		void SetUniform3fv(const std::string& name, const glm::vec3& vec);

		void SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat);

	private:
		int GetUniformID(const std::string& name) const;
		
		std::unique_ptr<unsigned, void(*)(unsigned*)> m_id;
	};
}