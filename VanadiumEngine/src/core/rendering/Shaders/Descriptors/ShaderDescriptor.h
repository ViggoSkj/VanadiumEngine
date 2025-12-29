#pragma once
#include "core/Rendering/GLCommon.h"
#include "core/Processing/Shader/Tokenizer/TokenizedShader.h"
#include "VertexShaderDescriptor.h"
#include "FragmentShaderDescriptor.h"

namespace Vanadium
{
	class ShaderDescriptor
	{
	public:
		static std::optional<ShaderDescriptor> Create(Vanadium::Detail::TokenizedShader tokenizedShader);

		ShaderDescriptor() = default;

		const UniformObjectDescriptor& FindUniformObjectDescriptor(std::string name) const;

		VertexShaderDescriptor VertexShader;
		FragmentShaderDescriptor FragmentShader;
	};
}