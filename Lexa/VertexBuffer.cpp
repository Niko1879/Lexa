#include <numeric>
#include <unordered_map>

#include "VertexBuffer.h"


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
		
		glBindVertexArray(*m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufs[1]);
	}


	VertexBuffer::VertexBuffer(std::vector<int> properties, Format format) : VertexBuffer(format)
	{
		Bind();
		for (int i : properties)
			AddProperty(i);
	}


	int VertexBuffer::GetSize() const
	{
		return m_nindices;
	}


	void VertexBuffer::SetVertexData(const std::vector<float>& data)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), m_format);
	}


	void VertexBuffer::SetIndexData(const std::vector<GLuint>& indices)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), m_format);
		m_nindices = indices.size();
	}


	void VertexBuffer::AddProperty(int size)
	{
		GenerateAttribPointer(size);
	}


	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufs[0]);
		glBindVertexArray(*m_vao);
	}


	void VertexBuffer::GenerateAttribPointer(GLint size)
	{
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
	}
}
