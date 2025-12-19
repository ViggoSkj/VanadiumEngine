#include "pch.h"
#include "IndexBuffer.h"
#include "GLCommon.h"

IndexBuffer::IndexBuffer()
{
	GL_CHECK(glGenBuffers(1, &m_id));
	m_count = 0;
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::UnBind() const
{
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count)
{
	Bind();
	m_count = count;
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	UnBind();
}
