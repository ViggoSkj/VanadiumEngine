#include "pch.h"
#include "VertexBuffer.h"
#include "GLCommon.h"

VertexBuffer::VertexBuffer()
{
	GL_CHECK(glCreateBuffers(1, &m_vertexBufferId));
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
	m_bufferSize = size;
	GL_CHECK(glNamedBufferData(m_vertexBufferId, size, data, usage));
}

void VertexBuffer::UpdateVertecies(const void* data, int size, int offset)
{
	Bind();
	if (size + offset > m_bufferSize)
		throw "buffer does not have enugh capacity";
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	UnBind();
}
