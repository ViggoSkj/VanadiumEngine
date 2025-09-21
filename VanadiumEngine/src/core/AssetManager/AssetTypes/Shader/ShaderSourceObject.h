#pragma once
#include "core/rendering/GLCommon.h"
#include "VertexShader.h"

struct FragmentShader
{

};

class ShaderSourceObject
{
public:
	ShaderSourceObject(std::string source);

private:
	FragmentShader m_fragmentShader;
	VertexShader m_vertexShader;
};