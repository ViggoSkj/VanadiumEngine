#include "core/rendering/GLCommon.h"
#include "GLUniformBuffer.h"


GLUniformBuffer::GLUniformBuffer(unsigned int size, GLenum usage)
{
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, usage);
}

GLUniformBuffer::~GLUniformBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void GLUniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}

void GLUniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GLUniformBuffer::SetData(void* data, unsigned int offset, unsigned int size)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glCheckError();
	UnBind();
}

void GLUniformBuffer::SetBindingPoint(unsigned int bindingPoint)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, m_id, 0, 2 * sizeof(float) * 4 * 4 * 2);
	glCheckError();
}
