#include "pch.h"
#include "core/Rendering/GLCommon.h"
#include "GLUniformBuffer.h"

namespace Vanadium
{
	GLUniformBuffer::GLUniformBuffer(unsigned int size, GLenum usage)
		: m_size(size)
	{
		GL_CHECK(glCreateBuffers(1, &m_id));
		Bind();
		GL_CHECK(glBufferData(GL_UNIFORM_BUFFER, m_size, NULL, usage));

	}

	GLUniformBuffer::GLUniformBuffer(const GLUniformBuffer& other)
		: ReferenceCounting(other), m_id(other.m_id), m_size(other.m_size)
	{
	}

	void GLUniformBuffer::Bind()
	{
		GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, m_id));
	}

	void GLUniformBuffer::UnBind()
	{
		GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, 0));
	}

	void GLUniformBuffer::SetData(void* data, unsigned int offset, unsigned int size)
	{
		Bind();
		GL_CHECK(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data));
		UnBind();
	}

	void GLUniformBuffer::SetBindingPoint(i32 uniformBindingSlot)
	{
		Bind();
		GL_CHECK(glBindBufferRange(GL_UNIFORM_BUFFER, uniformBindingSlot, m_id, 0, m_size));
	}
}