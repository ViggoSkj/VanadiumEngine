#include "ShaderSourceObject.h"
#include <vector>
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

ShaderSourceObject::ShaderSourceObject(std::string source)
{
	TokenizedShader shader = Tokenizer::Tokenize(source);

	int vertexShaderHint = shader.FindHint("#shader", "vertex");
	int fragmentShaderHint = shader.FindHint("#shader", "fragment");

	std::vector<int> all = {
		vertexShaderHint,
		fragmentShaderHint,
		(int) shader.Tokens().size()
	};

	int fragmentLength = SmallestPositiveDifference(fragmentShaderHint, all);
	int vertexLength = SmallestPositiveDifference(vertexShaderHint, all);

	std::vector<Token> VertexTokens = std::vector<Token>(shader.Tokens().begin() + vertexShaderHint + 2, shader.Tokens().begin() + vertexShaderHint + vertexLength);
	TokenizedShader tokenizedVertexShader(VertexTokens);
	std::vector<Token> FragmentTokens = std::vector<Token>(shader.Tokens().begin() + fragmentShaderHint + 2, shader.Tokens().begin() + fragmentShaderHint + fragmentLength);
	TokenizedShader tokenizedFragmentShader(FragmentTokens);

	// analyze vertex shader
	TokenizedVertexShaderAnalyzer::GetVertexAttributes(tokenizedVertexShader, m_vertexShader.VertexAttributes);
	TokenizedVertexShaderAnalyzer::GetUniformObjects(tokenizedVertexShader, m_vertexShader.UniformObjects);

	// analyzer fragment shader

}