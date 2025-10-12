#pragma once


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
	UniformObjectDescriptor() = default;
	UniformObjectDescriptor(std::string name, std::vector<UniformDescriptor> uniforms)
		: Name(name), Uniforms(uniforms) {
	};

	std::string Name;
	std::vector<UniformDescriptor> Uniforms;
};
