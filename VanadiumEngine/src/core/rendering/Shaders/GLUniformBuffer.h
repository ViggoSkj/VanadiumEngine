#pragma once
#include "core/AssetManager/AssetTypes/Shader/ShaderDataType.h"
#include "Shaders/UniformBindingSlot.h"

class GLUniformBuffer
{
public:

	GLUniformBuffer() = default;
	GLUniformBuffer(unsigned int size, GLenum usage=GL_STATIC_DRAW);
	~GLUniformBuffer();

	void Bind();
	void UnBind();

	void SetData(void* data, unsigned int offset, unsigned int size);

	void SetBindingPoint(UniformBindingSlot& uniformBindingSlot);
private:
	unsigned int m_id;
	unsigned int m_size;
};