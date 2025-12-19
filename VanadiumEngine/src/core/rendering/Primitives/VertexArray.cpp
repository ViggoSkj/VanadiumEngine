#include "pch.h"
#include "VertexArray.h"
#include "GLCommon.h"
#include "core/Debug/Log.h"


VertexArray::VertexArray()
{
	GL_CHECK(glGenVertexArrays(1, &m_vertexArrayId));
	m_vertexAttributeCount = 0;
}

VertexArray::~VertexArray()
{
	// LogDebug("Deleted vertex array with id " + std::to_string(m_vertexArrayId));
	GL_CHECK(glDeleteVertexArrays(1, &m_vertexArrayId));
}

void VertexArray::Bind()
{
	GL_CHECK(glBindVertexArray(m_vertexArrayId));
}

void VertexArray::UnBind()
{
	GL_CHECK(glBindVertexArray(0));
}

void VertexArray::AssignVertexAttributes(std::vector<GLVertexAttribute> attributes, int divisor, bool normalize)
{
	Bind();

	int stride = 0;

	if (attributes.size() > 0)
		for (int i = 0; i < attributes.size(); i++)
		{
			GLVertexAttribute a = attributes[i];
			stride += a.TypeSize * a.Count;
		}

	int offset = 0;
				
	for (int i = 0; i < attributes.size(); i++)
	{
		GLVertexAttribute a = attributes[i];
		GL_CHECK(glVertexAttribPointer(m_vertexAttributeCount + i, a.Count, a.Type, normalize, stride, (void*)(offset)));
		GL_CHECK(glEnableVertexAttribArray(m_vertexAttributeCount + i));
		GL_CHECK(glVertexAttribDivisor(m_vertexAttributeCount + i, divisor));
		offset += a.TypeSize * a.Count;
	}

	m_vertexAttributeCount += attributes.size();

	UnBind();
}
