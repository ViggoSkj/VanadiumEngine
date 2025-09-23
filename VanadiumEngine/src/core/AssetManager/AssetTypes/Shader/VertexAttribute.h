#pragma once
#include "ShaderDataType.h"

struct VertexAttribute
{
	ShaderDataType Type;
	unsigned int Location;

	VertexAttribute(ShaderDataType type, unsigned int location)
		: Type(type), Location(location) {
	};
};