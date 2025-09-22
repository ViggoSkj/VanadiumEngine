#pragma once
#include "core/rendering/GLCommon.h"
#include "core/AssetManager/AssetTypes/Shader/ShaderSourceObject.h"

class Shader
{
public:
	Shader();
	Shader(const Shader& other) = default;
	Shader(ShaderSourceObject sourceObject);
	~Shader();

	unsigned int GetId();
	bool LoadSource(const char* sourceFile);
	int GetUniformLocation(const char* name);
	void Use();
	void ConfigureUniformBlock(const char* blockName, unsigned int bindingPoint);

private:
	unsigned int m_shaderProgramId = 0;

	unsigned int CompileShader(const char* shaderSource, GLenum type);
};