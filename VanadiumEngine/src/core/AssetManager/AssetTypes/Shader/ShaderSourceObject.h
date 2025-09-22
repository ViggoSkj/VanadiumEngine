#pragma once
#include "core/rendering/GLCommon.h"
#include "ShaderTypes/VertexShader.h"
#include "ShaderTypes/FragmentShader.h"
#include "../../FileAsset.h"

class ShaderSourceObject : public FileAsset
{
public:
	ShaderSourceObject(std::string source);
	~ShaderSourceObject() {

	};

	FragmentShader m_fragmentShader;
	VertexShader m_vertexShader;
};