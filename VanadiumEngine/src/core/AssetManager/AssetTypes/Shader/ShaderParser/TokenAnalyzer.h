#pragma once
#include <vector>
#include "TokenizedShader.h"
#include "core/AssetManager/AssetTypes/Shader/VertexAttribute.h"
#include "../ShaderUniform.h"

namespace TokenizedVertexShaderAnalyzer
{
	void GetVertexAttributes(TokenizedShader& shader, std::vector<VertexAttribute>& vertexAttributes);
	void GetUniformObjects(TokenizedShader& shader, std::vector<UniformObjectDescriptor>& uniformObjects);
	void GetUniforms(TokenizedShader& shader, std::vector<UniformDescriptor>& uniforms);
}