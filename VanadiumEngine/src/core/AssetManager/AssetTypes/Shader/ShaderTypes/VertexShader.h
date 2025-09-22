#pragma once
#include <vector>
#include "../ShaderDataType.h"
#include "../ShaderUniform.h"
#include "ShaderBase.h"

struct VertexAttribute 
{
	ShaderDataType Type;
	unsigned int Location;

	VertexAttribute(ShaderDataType type, unsigned int location)
		: Type(type), Location(location) {
	};
};

struct VertexShader : public ShaderBase
{
	std::vector<VertexAttribute> VertexAttributes;
};