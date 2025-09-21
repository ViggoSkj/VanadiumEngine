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
	VertexArray(const VertexArray& other) = default;
	~VertexArray();

	void Bind();
	void UnBind();

	void AssignVertexAttributes(std::vector<GLVertexAttribute> attributes, int divisor = 0);

private:
	unsigned int m_vertexArrayId;
	unsigned int m_vertexAttributeCount;
};

