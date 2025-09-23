#pragma once
#include <string>
#include "core/AssetManager/AssetTypes/Shader/ShaderUniform.h"

struct ShaderBaseDescriptor
{
	std::vector<UniformObjectDescriptor> UniformObjects;
	std::vector<UniformDescriptor> Uniforms;
};