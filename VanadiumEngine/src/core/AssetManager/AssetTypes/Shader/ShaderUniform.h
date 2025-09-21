#pragma once
#include <string>
#include <vector>
#include "ShaderDataType.h"

struct ShaderUniform
{
	std::string name;
	ShaderDataType type;

	ShaderUniform(std::string name, ShaderDataType type)
		: name(name), type(type) {
	};
};

struct ShaderUniformObject
{
	std::string name;
	std::vector<ShaderUniform> uniforms;
};