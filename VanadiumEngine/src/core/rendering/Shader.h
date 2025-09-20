#pragma once
#include "core/rendering/GLCommon.h"

class Shader
{
public:
	Shader();
	Shader(const Shader& other) = default;
	~Shader();

	unsigned int GetId();
	bool LoadSource(const char* sourceFile);
	int GetUniformLocation(const char* name);
	void Use();

private:
	unsigned int m_shaderProgramId = 0;

	unsigned int CompileShader(const char* shaderSource, GLenum type);
};