#pragma once
#include "GLCommon.h"
#include "core/Processing/Shader/Tokenizer/TokenizedShader.h"
#include "VertexShaderDescriptor.h"
#include "FragmentShaderDescriptor.h"

class ShaderDescriptor
{
public:
	static std::optional<ShaderDescriptor> Create(TokenizedShader tokenizedShader);

	ShaderDescriptor() = default;
	
	const UniformObjectDescriptor& FindUniformObjectDescriptor(std::string name) const;

	VertexShaderDescriptor VertexShader;
	FragmentShaderDescriptor FragmentShader;
};