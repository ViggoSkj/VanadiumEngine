#pragma once
#include "core/rendering/GLCommon.h"

enum ShaderType
{
	Fragment = GL_FRAGMENT_SHADER,
	Vertex = GL_VERTEX_SHADER,
	Geometry = GL_GEOMETRY_SHADER,
	Compute = GL_COMPUTE_SHADER,
};

struct ShaderSource
{
	ShaderType Type;
	const char* Source;
};

class ShaderSourceObject
{
public:

private:

};

void TokenizeShaderSource(std::string source);