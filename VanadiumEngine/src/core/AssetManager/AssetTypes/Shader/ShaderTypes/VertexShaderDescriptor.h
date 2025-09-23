#pragma once
#include <vector>
#include "../ShaderDataType.h"
#include "../ShaderUniform.h"
#include "../VertexAttribute.h"
#include "../ShaderTypes/ShaderDescriptorBase.h"

struct VertexShaderDescriptor : public ShaderBaseDescriptor
{
	std::vector<VertexAttribute> VertexAttributes;
};