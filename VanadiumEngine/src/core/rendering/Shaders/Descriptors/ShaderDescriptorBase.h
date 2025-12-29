#pragma once

#include "core/Rendering/Shaders/ShaderUniform.h"

namespace Vanadium
{
	struct ShaderBaseDescriptor
	{
		bool UsesUniformObject(std::string name);

		std::vector<UniformObjectDescriptor> UniformObjects;
		std::vector<UniformDescriptor> Uniforms;
	};
}