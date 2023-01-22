#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "IO.h"


namespace Lexa
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragSrc);

		unsigned GetId() const;

		void SetUniform3fv(const std::string& name, const glm::vec3& vec);

		void SetUniform4fv(const std::string& name, const glm::vec4& vec);

		void SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat);

		void Bind() const;

	private:
		int GetUniformID(const std::string& name) const;
		
		std::unique_ptr<unsigned, void(*)(unsigned*)> m_id;
	};
}
