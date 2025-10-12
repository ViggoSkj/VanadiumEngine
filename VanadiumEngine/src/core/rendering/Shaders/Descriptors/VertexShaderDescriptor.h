#pragma once

#include "Shaders/ShaderDataType.h"
#include "Shaders/ShaderUniform.h"
#include "Shaders/VertexAttribute.h"
#include "Shaders/Descriptors/ShaderDescriptorBase.h"

struct VertexShaderDescriptor : public ShaderBaseDescriptor
{
	std::vector<VertexAttribute> VertexAttributes;
};