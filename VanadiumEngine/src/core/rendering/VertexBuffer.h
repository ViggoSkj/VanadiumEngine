#pragma once
#include "core/rendering/GLCommon.h"

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void UnBind();

	void SetVertecies(const void* data, int size, GLenum usage = GL_STATIC_DRAW);
	void UpdateVertecies(const void* data, int size, int offset = 0);

private:
	unsigned int m_vertexBufferId;
};