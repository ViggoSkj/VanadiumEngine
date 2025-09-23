#pragma once
#include <string>
#include <vector>
#include "ShaderDataType.h"

struct UniformDescriptor
{
	std::string name;
	ShaderDataType type;

	UniformDescriptor(std::string name, ShaderDataType type)
		: name(name), type(type) {
	};
};

struct UniformObjectDescriptor
{
	std::string name;
	std::vector<UniformDescriptor> uniforms;
};
