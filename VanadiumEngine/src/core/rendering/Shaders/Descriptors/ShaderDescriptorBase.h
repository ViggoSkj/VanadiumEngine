#pragma once
#include <string>
#include "Shaders/ShaderUniform.h"

struct ShaderBaseDescriptor
{
	bool UsesUniformObject(std::string name);

	std::vector<UniformObjectDescriptor> UniformObjects;
	std::vector<UniformDescriptor> Uniforms;
};