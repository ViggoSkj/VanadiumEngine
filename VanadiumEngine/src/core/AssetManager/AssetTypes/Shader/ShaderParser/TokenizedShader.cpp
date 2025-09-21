#include "TokenizedShader.h"
#include "../ShaderKeywordMaps.h"

TokenizedShader::TokenizedShader(std::vector<Token>& tokens)
{
	m_tokens = std::move(tokens);
}

int TokenizedShader::FindToken(TokenType type, unsigned int offset)
{
	for (int i = 0; i < m_tokens.size(); i++)
	{
		if (m_tokens[i].Type == type)
			return i;
	}

	return -1;
}

int TokenizedShader::FindKeyword(ShaderKeyword keyword, unsigned int offset)
{
	for (int i = offset; i < m_tokens.size(); i++)
	{
		if (m_tokens[i].Type == TokenType::Keyword && m_tokens[i].Text == ShaderKeywordToString.at(keyword))
			return i;
	}

	return -1;
}