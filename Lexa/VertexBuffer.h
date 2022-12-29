#pragma once
#include <vector>
#include <memory>

#include "glad/glad.h"

namespace Lexa
{
	class VertexBuffer
	{
		friend class RenderState;

	public:
		enum class Format
		{
			STATIC,
			DYNAMIC
		};

		VertexBuffer(Format format = Format::STATIC);

		VertexBuffer(std::vector<int> properties, Format format = Format::STATIC);

		void AddProperty(int size);

		void AddData(const std::vector<float>& data);

		void AddIndices(const std::vector<unsigned>& indices);

		int GetSize() const;

	private:
		void GenerateAttribPointer(int size);

		std::unique_ptr<unsigned, void(*)(unsigned*)> m_vao;
		std::unique_ptr<unsigned[], void(*)(unsigned*)> m_bufs;
		std::vector<GLuint> m_attribPointerSizes;
		int m_nindices;
		unsigned m_format;
	};
}

