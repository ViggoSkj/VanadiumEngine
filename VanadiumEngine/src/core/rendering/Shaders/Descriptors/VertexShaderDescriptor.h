#pragma once

#include "core/Rendering/Shaders/ShaderDataType.h"
#include "core/Rendering/Shaders/ShaderUniform.h"
#include "core/Rendering/Shaders/VertexAttribute.h"
#include "core/Rendering/Shaders/Descriptors/ShaderDescriptorBase.h"

namespace Vanadium
{
	struct VertexShaderDescriptor : public ShaderBaseDescriptor
	{
		std::vector<VertexAttribute> VertexAttributes;
	};
}