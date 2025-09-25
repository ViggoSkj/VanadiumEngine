#pragma once
#include "AssetTypes/Shader/ShaderDescriptor.h"
#include "Shaders/GLShader.h"
#include "Shaders/UniformObject.h"

class Shader
{
public:
	Shader(std::string source);

	// uses the uniform object if it is needed
	void ReportUniformObject(UniformObject object);

	const GLShader& GlShader() { return m_shaderProgram; };
	const ShaderDescriptor& Descriptor() { return m_shaderDescriptor; };

private:
	ShaderDescriptor m_shaderDescriptor;
	GLShader m_shaderProgram;
};