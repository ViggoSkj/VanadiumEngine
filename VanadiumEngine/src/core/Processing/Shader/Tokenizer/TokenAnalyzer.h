#pragma once
#include "pch.h"
#include "TokenizedShader.h"
#include "Shaders/VertexAttribute.h"
#include "Shaders/ShaderUniform.h"

namespace TokenizedVertexShaderAnalyzer
{
	void GetVertexAttributes(TokenizedShader& shader, std::vector<VertexAttribute>& vertexAttributes);
	void GetUniformObjects(TokenizedShader& shader, std::vector<UniformObjectDescriptor>& uniformObjects);
	void GetUniforms(TokenizedShader& shader, std::vector<UniformDescriptor>& uniforms);
}