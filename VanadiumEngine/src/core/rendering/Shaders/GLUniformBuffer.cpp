#include "core/rendering/GLCommon.h"
#include "GLUniformBuffer.h"


GLUniformBuffer::GLUniformBuffer(unsigned int size, GLenum usage)
	: m_size(size)
{
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_UNIFORM_BUFFER, m_size, NULL, usage);

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
	UnBind();
}

void GLUniformBuffer::SetBindingPoint(UniformBindingSlot& uniformBindingSlot)
{
	Bind();
	glBindBufferRange(GL_UNIFORM_BUFFER, uniformBindingSlot.Slot, m_id, 0, m_size);
}
