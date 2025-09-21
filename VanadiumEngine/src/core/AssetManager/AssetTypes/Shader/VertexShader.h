#pragma once
#include <vector>
#include "ShaderDataType.h"
#include "ShaderUniform.h"

struct VertexAttribute
{
	ShaderDataType Type;
	unsigned int Location;

	VertexAttribute(ShaderDataType type, unsigned int location)
		: Type(type), Location(location) {
	};
};

class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	std::vector<VertexAttribute> VertexAttributes;
	std::vector<ShaderUniformObject> UniformObjects;
};