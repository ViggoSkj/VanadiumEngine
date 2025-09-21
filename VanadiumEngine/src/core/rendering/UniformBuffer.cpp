#include "UniformBuffer.h"
#include "core/rendering/GLCommon.h"

UniformBuffer::UniformBuffer()
{
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_UNIFORM_BUFFER, 16 * 2 * 4, NULL, GL_STATIC_DRAW);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}

void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::SetData(void* data, unsigned int offset, unsigned int size)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	UnBind();
}

void UniformBuffer::SetBindingPoint(unsigned int bindingPoint)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, m_id, 0, 2 * sizeof(float) * 4 * 4 * 2);
	glCheckError();
}
