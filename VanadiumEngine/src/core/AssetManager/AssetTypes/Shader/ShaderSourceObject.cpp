#include "ShaderSourceObject.h"
#include <vector>
#include <fstream>
#include "ShaderParser/ShaderTokenizer.h"
#include "ShaderParser/TokenAnalyzer.h"

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

ShaderSourceObject::ShaderSourceObject(std::string filePath)
{
	std::string source;

	std::fstream stream(filePath);
	std::string line;

	while (std::getline(stream, line))
	{
		source += line + "\n";
	}

	TokenizedShader shader = Tokenizer::Tokenize(source);

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
	m_vertexShader.Source = source.substr(VertexTokens.front().SourceIndex, VertexTokens.back().SourceIndex - VertexTokens.front().SourceIndex + 1);
	TokenizedShader tokenizedVertexShader(VertexTokens);

	std::vector<Token> FragmentTokens = std::vector<Token>(shader.Tokens().begin() + fragmentShaderHint + 2, shader.Tokens().begin() + fragmentShaderHint + fragmentLength);
	m_fragmentShader.Source = source.substr(FragmentTokens.front().SourceIndex, FragmentTokens.back().SourceIndex - FragmentTokens.front().SourceIndex + 1);
	TokenizedShader tokenizedFragmentShader(FragmentTokens);


	// analyze vertex shader
	TokenizedVertexShaderAnalyzer::GetVertexAttributes(tokenizedVertexShader, m_vertexShader.VertexAttributes);
	TokenizedVertexShaderAnalyzer::GetUniformObjects(tokenizedVertexShader, m_vertexShader.UniformObjects);
	TokenizedVertexShaderAnalyzer::GetUniforms(tokenizedVertexShader, m_vertexShader.Uniforms);

	// analyzer fragment shader
	TokenizedVertexShaderAnalyzer::GetUniformObjects(tokenizedFragmentShader, m_fragmentShader.UniformObjects);
	TokenizedVertexShaderAnalyzer::GetUniforms(tokenizedFragmentShader, m_fragmentShader.Uniforms);
}