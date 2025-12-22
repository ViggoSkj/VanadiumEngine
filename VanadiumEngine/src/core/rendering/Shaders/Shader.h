#pragma once
#include "Descriptors/ShaderDescriptor.h"
#include "GLShader.h"
#include "UniformObject.h"
#include "core/IO/IFileLoader.h"


class Shader
{
public:
	static std::optional<Shader> CreateShader(std::string source, ShaderDescriptor descriptor);
	Shader(std::string source, ShaderDescriptor descriptor);

	// uses the uniform object if it is needed
	void ReportUniformObject(UniformObject object);

	const GLShader& GlShader() { return m_shaderProgram; };
	const ShaderDescriptor& Descriptor() { return m_shaderDescriptor; };

private:
	ShaderDescriptor m_shaderDescriptor;
	GLShader m_shaderProgram;
};