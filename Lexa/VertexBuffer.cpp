#include <numeric>
#include <unordered_map>

#include "VertexBuffer.h"
#include "RenderState.h"

namespace Lexa
{
	static const std::unordered_map<VertexBuffer::Format, GLenum> s_Format
	{
		{VertexBuffer::Format::STATIC, GL_STATIC_DRAW},
		{VertexBuffer::Format::DYNAMIC, GL_DYNAMIC_DRAW}
	};


	VertexBuffer::VertexBuffer(Format format) :
		m_bufs(nullptr, [](GLuint* ptr) { glDeleteBuffers(2, ptr); }),
		m_vao(nullptr, [](GLuint* ptr) { glDeleteVertexArrays(1, ptr); }),
		m_nindices(0),
		m_format(s_Format.at(format))
	{
		GLuint bufs[2], vao;

		glGenBuffers(2, &bufs[0]);
		m_bufs.reset(new GLuint[2]{ bufs[0], bufs[1] });

		glGenVertexArrays(1, &vao);
		m_vao.reset(new GLuint(vao));

		RenderState& rs = RenderState::Instance();
		std::weak_ptr<VertexBuffer> oldVao = rs.GetVertexBuffer();
		
		glBindVertexArray(*m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufs[1]);
		glBindVertexArray(oldVao.expired() ? 0 : *oldVao.lock()->m_vao);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldVao.expired() ? 0 : oldVao.lock()->m_bufs[1]);
	}


	VertexBuffer::VertexBuffer(std::vector<int> properties, Format format) : VertexBuffer(format)
	{
		for (int i : properties)
			AddProperty(i);
	}


	void VertexBuffer::AddProperty(int size)
	{
		GenerateAttribPointer(size);
	}


	void VertexBuffer::AddData(const std::vector<float>& data)
	{
		std::weak_ptr<VertexBuffer> activeVao = RenderState::Instance().GetVertexBuffer();
		bool isCurrent = !activeVao.expired() && *activeVao.lock()->m_vao == *m_vao;

		if (!isCurrent)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufs[0]);
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), m_format);

		if (!isCurrent)
		{
			glBindBuffer(GL_ARRAY_BUFFER, activeVao.expired() ? 0 : activeVao.lock()->m_bufs[0]);
		}
	}


	void VertexBuffer::AddIndices(const std::vector<GLuint>& indices)
	{
		std::weak_ptr<VertexBuffer> activeVao = RenderState::Instance().GetVertexBuffer();
		bool isCurrent = !activeVao.expired() && *activeVao.lock()->m_vao == *m_vao;

		if (!isCurrent)
		{
			glBindVertexArray(*m_vao);
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), m_format);
		m_nindices = indices.size();

		if (!isCurrent)
		{
			glBindVertexArray(activeVao.expired() ? 0 : *activeVao.lock()->m_vao);
		}
	}


	int VertexBuffer::GetSize() const
	{
		return m_nindices;
	}


	void VertexBuffer::GenerateAttribPointer(GLint size)
	{
		std::weak_ptr<VertexBuffer> activeVao = RenderState::Instance().GetVertexBuffer();
		bool isCurrent = !activeVao.expired() && *activeVao.lock()->m_vao == *m_vao;

		if (!isCurrent)
		{
			glBindVertexArray(*m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_bufs[0]);
		}

		m_attribPointerSizes.push_back(size);
		GLint stride = std::accumulate(m_attribPointerSizes.begin(), m_attribPointerSizes.end(), 0);
		GLint offset = stride - size;
		GLint n_attribPtr = m_attribPointerSizes.size() - 1;
		glVertexAttribPointer(n_attribPtr, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(n_attribPtr);
		for (GLint i = m_attribPointerSizes.size() - 2; i >= 0; --i)
		{
			size = m_attribPointerSizes[i];
			offset -= size;
			glVertexAttribPointer(--n_attribPtr, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		}

		if (!isCurrent)
		{
			glBindVertexArray(activeVao.expired() ? 0 : *activeVao.lock()->m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, activeVao.expired() ? 0 : activeVao.lock()->m_bufs[0]);
		}
	}
}
