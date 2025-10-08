#include "VertexBuffer.h"
#include "GLCommon.h"

VertexBuffer::VertexBuffer()
{
	GL_CHECK(glGenBuffers(1, &m_vertexBufferId));
}

VertexBuffer::~VertexBuffer()
{
	GL_CHECK(glDeleteBuffers(1, &m_vertexBufferId));
}

void VertexBuffer::Bind()
{
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));
}

void VertexBuffer::UnBind()
{
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetVertecies(const void* data, int size, GLenum usage)
{
	Bind();
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
	UnBind();
}

void VertexBuffer::UpdateVertecies(const void* data, int size, int offset)
{
	Bind();
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	UnBind();
}
