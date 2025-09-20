#include "VertexBuffer.h"
#include "core/rendering/GLCommon.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_vertexBufferId);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vertexBufferId);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetVertecies(const void* data, int size, GLenum usage)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glCheckError();
	UnBind();
}

void VertexBuffer::UpdateVertecies(const void* data, int size, int offset)
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	glCheckError();
	UnBind();
}
