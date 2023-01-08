#include "SurfaceRenderer.h"


namespace Lexa
{
	glm::vec3 ComputeCentroid(const std::vector<float>& vertices, int numAttrib)
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		size_t n = vertices.size() / numAttrib;
		for (size_t i = 0; i < vertices.size() - 3; i += 3)
		{
			x += vertices[i];
			y += vertices[i + 1];
			z += vertices[i + 2];
		}

		return glm::vec3(x / n, y / n, z / n);
	}


	std::vector<float> ComputeNormals(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
	{
		std::unordered_map<unsigned int, std::vector<std::vector<float>>> indexToTriangle;

		for (size_t i = 0; i < indices.size() - 2; i += 3)
		{
			unsigned int i1 = indices[i];
			unsigned int i2 = indices[i + 1];
			unsigned int i3 = indices[i + 2];
			std::vector<float> t = {
				vertices[3*i1], vertices[3*i1 + 1], vertices[3*i1 + 2],
				vertices[3*i2], vertices[3*i2 + 1], vertices[3*i2 + 2],
				vertices[3*i3], vertices[3*i3 + 1], vertices[3*i3 + 2]
			};
			indexToTriangle[i1].push_back(t);
			indexToTriangle[i2].push_back(t);
			indexToTriangle[i3].push_back(t);
		}

		std::vector<float> vertexNormals;
		vertexNormals.resize(vertices.size());

		for (auto& pair: indexToTriangle)
		{
			unsigned int i = pair.first;
			std::vector<glm::vec3> normals;
			for (const std::vector<float>& t : indexToTriangle[i])
			{
				glm::vec3 p1(t[0], t[1], t[2]);
				glm::vec3 p2(t[3], t[4], t[5]);
				glm::vec3 p3(t[6], t[7], t[8]);
				glm::vec3 v1 = p2 - p1;
				glm::vec3 v2 = p3 - p1;
				glm::vec3 normal = glm::cross(v2, v1);
				normals.push_back(normal);
			}

			glm::vec3 norm(0.0f, 0.0f, 0.0f);
			for (glm::vec3& vec : normals)
				norm += vec;
			norm /= normals.size();
			norm = glm::normalize(norm);
			vertexNormals[3*i] = norm.x;
			vertexNormals[3*i + 1] = norm.y;
			vertexNormals[3*i + 2] = norm.z;
		}

		return vertexNormals;
	}

	
	SurfaceRenderer::SurfaceRenderer() 
		: m_vao(std::vector<int>{3, 3}),
		  m_centroid(0.f)
	{

	}


	const VertexBuffer& SurfaceRenderer::GetGeometry() const
	{
		return m_vao;
	}


	void SurfaceRenderer::Generate(const Interpreter::Eval2D& eval, float xmin, float xmax, float ymin, float ymax, float step)
	{
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		float tolerance = step / 10.0f;
		for (float x = xmin; x < xmax + tolerance; x += step)
		{
			for (float y = ymin; y < ymax + tolerance; y += step)
			{
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(eval(x, y));
			}
		}

		size_t xCount = round((xmax - xmin) / step);
		size_t yCount = round((ymax - ymin) / step);
		++xCount;
		++yCount;

		for (size_t j = 0; j < yCount - 1; ++j)
		{
			for (size_t i = j; i <= vertices.size() / 3 - yCount - 1; i += yCount)
			{
				indices.push_back(i);
				indices.push_back(i + yCount);
				indices.push_back(i + 1);
				indices.push_back(i + 1);
				indices.push_back(i + yCount);
				indices.push_back(i + yCount + 1);
			}
		}

		m_centroid = ComputeCentroid(vertices, 3);
		std::vector<float> normals = ComputeNormals(vertices, indices);

		//interlace normals with vertices
		std::vector<float> vertexAttributes;
		for (size_t i = 0; i < normals.size() - 2; i += 3)
		{
			vertexAttributes.push_back(vertices[i]);
			vertexAttributes.push_back(vertices[i + 1]);
			vertexAttributes.push_back(vertices[i + 2]);
			vertexAttributes.push_back(normals[i]);
			vertexAttributes.push_back(normals[i + 1]);
			vertexAttributes.push_back(normals[i + 2]);
		}

		m_vao.SetVertexData(vertexAttributes);
		m_vao.SetIndexData(indices);
	}


	const glm::vec3& SurfaceRenderer::GetCentroid() const
	{
		return m_centroid;
	}
}
