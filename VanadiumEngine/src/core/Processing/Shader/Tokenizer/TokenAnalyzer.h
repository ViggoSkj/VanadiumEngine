#pragma once
#include "pch.h"
#include "TokenizedShader.h"
#include "core/Rendering/Shaders/VertexAttribute.h"
#include "core/Rendering/Shaders/ShaderUniform.h"

namespace Vanadium::Detail::TokenAnalyzer
{
	void GetVertexAttributes(TokenizedShader& shader, std::vector<VertexAttribute>& vertexAttributes);
	void GetUniformObjects(TokenizedShader& shader, std::vector<UniformObjectDescriptor>& uniformObjects);
	void GetUniforms(TokenizedShader& shader, std::vector<UniformDescriptor>& uniforms);
}