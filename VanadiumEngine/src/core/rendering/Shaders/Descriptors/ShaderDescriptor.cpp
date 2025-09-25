#include "ShaderDescriptor.h"
#include <vector>
#include <fstream>
#include "core/Proccessing/Shader/ShaderTokenizer.h"
#include "core/Proccessing/Shader/TokenAnalyzer.h"

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

ShaderDescriptor::ShaderDescriptor(TokenizedShader shader)
{

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
		std::cout << "no fragment shader hint";
	if (vertexShaderHint== -1)
		std::cout << "no vertex shader hint";

	std::vector<Token> VertexTokens = std::vector<Token>(shader.Tokens().begin() + vertexShaderHint + 2, shader.Tokens().begin() + vertexShaderHint + vertexLength);
	//VertexShader.Source = source.substr(VertexTokens.front().SourceIndex, VertexTokens.back().SourceIndex - VertexTokens.front().SourceIndex + 1);
	TokenizedShader tokenizedVertexShader(VertexTokens);

	std::vector<Token> FragmentTokens = std::vector<Token>(shader.Tokens().begin() + fragmentShaderHint + 2, shader.Tokens().begin() + fragmentShaderHint + fragmentLength);
	//FragmentShader.Source = source.substr(FragmentTokens.front().SourceIndex, FragmentTokens.back().SourceIndex - FragmentTokens.front().SourceIndex + 1);
	TokenizedShader tokenizedFragmentShader(FragmentTokens);


	// analyze vertex shader
	TokenizedVertexShaderAnalyzer::GetVertexAttributes(tokenizedVertexShader, VertexShader.VertexAttributes);
	TokenizedVertexShaderAnalyzer::GetUniformObjects(tokenizedVertexShader, VertexShader.UniformObjects);
	TokenizedVertexShaderAnalyzer::GetUniforms(tokenizedVertexShader, VertexShader.Uniforms);

	// analyzer fragment shader
	TokenizedVertexShaderAnalyzer::GetUniformObjects(tokenizedFragmentShader, FragmentShader.UniformObjects);
	TokenizedVertexShaderAnalyzer::GetUniforms(tokenizedFragmentShader, FragmentShader.Uniforms);
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
