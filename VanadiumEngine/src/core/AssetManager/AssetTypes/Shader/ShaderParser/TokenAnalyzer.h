#pragma once
#include <vector>
#include "TokenizedShader.h"
#include "../ShaderTypes/VertexShader.h"
#include "../ShaderUniform.h"

namespace TokenizedVertexShaderAnalyzer
{
	void GetVertexAttributes(TokenizedShader& shader, std::vector<VertexAttribute>& vertexAttributes);
	void GetUniformObjects(TokenizedShader& shader, std::vector<ShaderUniformObject>& uniformObjects);
	void GetUniforms(TokenizedShader& shader, std::vector<ShaderUniform>& uniforms);
}