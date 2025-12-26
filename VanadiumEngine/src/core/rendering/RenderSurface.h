#pragma once
#include "pch.h"
#include "core/rendering/Primitives/IndexBuffer.h"
#include "core/rendering/Primitives/VertexBuffer.h"
#include "core/rendering/Primitives/VertexArray.h"

class RenderSurface
{
public:
	RenderSurface(std::array<float, 4 * 5> meshVertices);

	size_t CreateVertexBuffer(std::vector<GLVertexAttribute> attributes, i32 divisor, i32 count, GLenum usage);
	void Resize(i32 buffer, i32 count);
private:
	VertexArray m_vertexArray;
	IndexBuffer m_indexBuffer;
	VertexBuffer m_meshVertices;

	std::vector<VertexBuffer> m_vertexBuffers;
	std::vector<i32>
};