#include "pch.h"
#include "RenderSurface.h"

RenderSurface::RenderSurface(std::array<float, 4 * 5> meshVertices)
{
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	m_vertexArray.Bind();

	m_meshVertices.SetVertecies(meshVertices.data(), meshVertices.size() * sizeof(float), GL_STATIC_DRAW);
	m_meshVertices.Bind();

	m_indexBuffer.SetData(indices, sizeof(indices));
	m_indexBuffer.Bind();

	m_vertexArray.AssignVertexAttributes({
		{sizeof(float), GL_FLOAT, 3},
		{sizeof(float), GL_FLOAT, 2},
	});
}

size_t RenderSurface::CreateVertexBuffer(std::vector<GLVertexAttribute> attributes, i32 divisor, i32 count, GLenum usage)
{
	m_vertexBuffers.emplace_back();
	VertexBuffer& buffer = m_vertexBuffers.back();
	buffer.Bind();

	i32 vertexSize = 0;
	for (GLVertexAttribute a : attributes)
		vertexSize += a.Count * a.TypeSize;
	buffer.SetVertecies(nullptr, count * vertexSize, usage);
	m_vertexArray.AssignVertexAttributes(attributes, divisor);

	return m_vertexBuffers.size() - 1;
}

void RenderSurface::Resize(i32 buffer, i32 count)
{
}