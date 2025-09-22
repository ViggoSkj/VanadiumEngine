#pragma once
#include "../ShaderUniform.h"
#include <string>

struct ShaderBase
{
	std::vector<ShaderUniformObject> UniformObjects;
	std::vector<ShaderUniform> Uniforms;

	std::string Source;
};