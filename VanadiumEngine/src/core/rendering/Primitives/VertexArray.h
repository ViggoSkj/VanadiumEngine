#pragma once
#include "GLCommon.h"
#include "IndexBuffer.h"

struct GLVertexAttribute
{
	GLVertexAttribute(int typeSize, int type, int count)
		: TypeSize(typeSize)
		, Type(type)
		, Count(count)
		, Normalize(GL_FALSE)
	{

	}

	GLVertexAttribute(int typeSize, int type, int count, GLenum normalize)
		: TypeSize(typeSize)
		, Type(type)
		, Count(count)
		, Normalize(normalize)
	{

	}

	int TypeSize;
	int Type;
	int Count;
	GLenum Normalize;
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

	void AssignVertexAttributes(std::vector<GLVertexAttribute> attributes, int divisor = 0);
private:
	unsigned int m_vertexArrayId = 0;
	unsigned int m_vertexAttributeCount = 0;
};

