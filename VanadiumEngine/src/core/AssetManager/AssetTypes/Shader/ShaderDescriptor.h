#pragma once
#include "core/rendering/GLCommon.h"
#include "ShaderParser/TokenizedShader.h"
#include "ShaderTypes/VertexShaderDescriptor.h"
#include "ShaderTypes/FragmentShaderDescriptor.h"
#include "../../FileAsset.h"

class ShaderDescriptor
{
public:
	ShaderDescriptor(TokenizedShader tokenizedShader);
	
	const UniformObjectDescriptor& FindUniformObjectDescriptor(std::string name) const;

	VertexShaderDescriptor VertexShader;
	FragmentShaderDescriptor FragmentShader;
};