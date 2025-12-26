#pragma once
#include "GLCommon.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct GLVertexAttribute
{
	GLVertexAttribute(GLenum type, u32 count, GLenum normalized);

	GLenum type;
	u32 count;
	GLenum normalized;

	u32 Size();
};

class VertexArray
{
public:
	VertexArray();
	VertexArray(VertexArray& other) = delete;
	VertexArray(VertexArray&& other) noexcept
		: m_vertexArrayId(std::move(other.m_vertexArrayId)), m_vertexAttributeCount(std::move(other.m_vertexAttributeCount))
	{
		other.m_vertexArrayId = 0;
		other.m_vertexAttributeCount = 0;
	};
	~VertexArray();

	VertexArray& operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			this->m_vertexArrayId = other.m_vertexArrayId;
			this->m_vertexAttributeCount = other.m_vertexAttributeCount;

			other.m_vertexArrayId = 0;
			other.m_vertexAttributeCount = 0;
		}

		return *this;
	}

	void Bind();
	void UnBind();

	void BindIndexBuffer(IndexBuffer& indexBuffer);

	u32 AddVertexAttributes(std::vector<GLVertexAttribute> attributes, u32 bindingIndex, u32 divisor = 0);
	void BindVertexBuffer(u32 bindingIndex, VertexBuffer& vertexBuffer, u32 offset, u32 stride);

	void AddVertexBuffer(std::vector<GLVertexAttribute> attributes, VertexBuffer& vertexBuffer, u32 bindingIndex, u32 divisor = 0);
private:
	u32 m_vertexArrayId = 0;
	u32 m_vertexAttributeCount = 0;
};

