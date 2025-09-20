#include "VertexArray.h"
#include "core/rendering/GLCommon.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayId);
	m_vertexAttributeCount = 0;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayId);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_vertexArrayId);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::AssignVertexAttributes(std::vector<VertexAttribute> attributes, int divisor)
{
	Bind();

	int stride = 0;

	for (int i = 0; i < attributes.size(); i++)
	{
		VertexAttribute a = attributes[i];
		stride += a.TypeSize * a.Count;
	}

	int offset = 0;

	for (int i = 0; i < attributes.size(); i++)
	{
		VertexAttribute a = attributes[i];
		glVertexAttribPointer(m_vertexAttributeCount + i, a.Count, a.Type, GL_FALSE, stride, (void*)(offset));
		glCheckError();
		glEnableVertexAttribArray(m_vertexAttributeCount + i);
		glCheckError();
		glVertexAttribDivisor(m_vertexAttributeCount + i, divisor);
		offset += a.TypeSize * a.Count;
	}

	m_vertexAttributeCount += attributes.size();

	UnBind();
}
