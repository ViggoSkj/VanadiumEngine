#pragma once
#include "ShaderDataType.h"
#include "core/util/ReferenceCounting.h"
#include "Shaders/UniformBindingSlot.h"

class GLUniformBuffer : ReferenceCounting
{
public:

	GLUniformBuffer() = default;
	GLUniformBuffer(unsigned int size, GLenum usage=GL_STATIC_DRAW);
	GLUniformBuffer(const GLUniformBuffer& other);

	void Bind();
	void UnBind();

	void SetData(void* data, unsigned int offset, unsigned int size);

	void SetBindingPoint(UniformBindingSlot& uniformBindingSlot);

protected:
	void Dispose() override {
		GL_CHECK(glDeleteProgram(m_id));
	};

private:
	unsigned int m_id;
	unsigned int m_size;
};