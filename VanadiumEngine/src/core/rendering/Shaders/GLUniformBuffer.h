#pragma once
#include "core/AssetManager/AssetTypes/Shader/ShaderDataType.h"

class GLUniformBuffer
{
public:
	GLUniformBuffer(unsigned int size, GLenum usage=GL_STATIC_DRAW);
	~GLUniformBuffer();

	void Bind();
	void UnBind();

	void SetData(void* data, unsigned int offset, unsigned int size);

	void SetBindingPoint(unsigned int bindingPoint);
private:
	unsigned int m_id;
};