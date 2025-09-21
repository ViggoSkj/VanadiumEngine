#pragma once
#include <vector>
#include "ShaderDataType.h"

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

private:
	std::vector<VertexAttribute> m_vertexAttributes;
};