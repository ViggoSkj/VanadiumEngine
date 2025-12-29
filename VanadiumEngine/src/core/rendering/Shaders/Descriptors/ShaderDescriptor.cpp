#include "pch.h"
#include <fstream>
#include "ShaderDescriptor.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"
#include "core/Processing/Shader/Tokenizer/TokenAnalyzer.h"
#include "core/Debug/Log.h"

namespace Vanadium
{
	int SmallestPositiveDifference(int self, std::vector<int> others)
	{
		int smallest = INT_MAX;
		for (int i = 0; i < others.size(); i++)
		{
			int diff = others[i] - self;
			if (diff > 0 && diff < smallest)
				smallest = diff;
		}

		return smallest;
	}

	std::optional<ShaderDescriptor> ShaderDescriptor::Create(Detail::TokenizedShader shader)
	{
		ShaderDescriptor descriptor;

		int vertexShaderHint = shader.FindHint("#shader", "vertex");
		int fragmentShaderHint = shader.FindHint("#shader", "fragment");

		std::vector<int> all = {
			vertexShaderHint,
			fragmentShaderHint,
			(int)shader.Tokens().size()
		};

		int fragmentLength = SmallestPositiveDifference(fragmentShaderHint, all);
		int vertexLength = SmallestPositiveDifference(vertexShaderHint, all);

		if (fragmentShaderHint == -1)
		{
			LogDebug("no fragment shader hint");
			return std::nullopt;
		}
		if (vertexShaderHint == -1)
		{
			LogDebug("no vertex shader hint");
			return std::nullopt;
		}

		std::vector<Vanadium::Detail::Token> VertexTokens = std::vector<Vanadium::Detail::Token>(shader.Tokens().begin() + vertexShaderHint + 2, shader.Tokens().begin() + vertexShaderHint + vertexLength);
		//VertexShader.Source = source.substr(VertexTokens.front().SourceIndex, VertexTokens.back().SourceIndex - VertexTokens.front().SourceIndex + 1);
		Vanadium::Detail::TokenizedShader tokenizedVertexShader(VertexTokens);

		std::vector<Vanadium::Detail::Token> FragmentTokens = std::vector<Vanadium::Detail::Token>(shader.Tokens().begin() + fragmentShaderHint + 2, shader.Tokens().begin() + fragmentShaderHint + fragmentLength);
		//FragmentShader.Source = source.substr(FragmentTokens.front().SourceIndex, FragmentTokens.back().SourceIndex - FragmentTokens.front().SourceIndex + 1);
		Vanadium::Detail::TokenizedShader tokenizedFragmentShader(FragmentTokens);

		// analyze vertex shader
		Vanadium::Detail::TokenAnalyzer::GetVertexAttributes(tokenizedVertexShader, descriptor.VertexShader.VertexAttributes);
		Vanadium::Detail::TokenAnalyzer::GetUniformObjects(tokenizedVertexShader, descriptor.VertexShader.UniformObjects);
		Vanadium::Detail::TokenAnalyzer::GetUniforms(tokenizedVertexShader, descriptor.VertexShader.Uniforms);

		// analyzer fragment shader
		Vanadium::Detail::TokenAnalyzer::GetUniformObjects(tokenizedFragmentShader, descriptor.FragmentShader.UniformObjects);
		Vanadium::Detail::TokenAnalyzer::GetUniforms(tokenizedFragmentShader, descriptor.FragmentShader.Uniforms);

		return descriptor;
	}

	const UniformObjectDescriptor& ShaderDescriptor::FindUniformObjectDescriptor(std::string name) const
	{
		for (int i = 0; i < VertexShader.UniformObjects.size(); i++)
		{
			if (VertexShader.UniformObjects[i].Name == name)
				return VertexShader.UniformObjects[i];
		}

		for (int i = 0; i < FragmentShader.UniformObjects.size(); i++)
		{
			if (FragmentShader.UniformObjects[i].Name == name)
				return FragmentShader.UniformObjects[i];
		}
	}

}