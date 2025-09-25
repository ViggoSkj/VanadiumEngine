#pragma once
#include "GLCommon.h"
#include "core/Proccessing/Shader/TokenizedShader.h"
#include "VertexShaderDescriptor.h"
#include "FragmentShaderDescriptor.h"

class ShaderDescriptor
{
public:
	ShaderDescriptor(TokenizedShader tokenizedShader);
	
	const UniformObjectDescriptor& FindUniformObjectDescriptor(std::string name) const;

	VertexShaderDescriptor VertexShader;
	FragmentShaderDescriptor FragmentShader;
};