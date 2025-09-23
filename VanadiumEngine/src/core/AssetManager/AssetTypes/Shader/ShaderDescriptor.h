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
	
	VertexShaderDescriptor VertexShader;
	FragmentShaderDescriptor FragmentShader;
};