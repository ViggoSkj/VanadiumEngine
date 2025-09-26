#pragma once
#include <vector>
#include "IndexBuffer.h"

struct GLVertexAttribute
{
	int TypeSize;
	int Type;
	int Count;
};

class VertexArray
{
public:
	VertexArray();
	VertexArray(VertexArray& other) = delete;
	VertexArray(VertexArray&& other) noexcept
		: m_vertexArrayId(std::move(other.m_vertexArrayId)), m_vertexAttributeCount(std::move(other.m_vertexAttributeCount)) {
	};
	~VertexArray();

	void Bind();
	void UnBind();

	void AssignVertexAttributes(std::vector<GLVertexAttribute> attributes, int divisor = 0);

private:
	unsigned int m_vertexArrayId = 0;
	unsigned int m_vertexAttributeCount = 0;
};

