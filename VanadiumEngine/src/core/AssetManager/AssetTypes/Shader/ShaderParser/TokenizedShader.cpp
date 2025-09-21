#include "TokenizedShader.h"
#include "../ShaderKeywordMaps.h"

TokenizedShader::TokenizedShader(std::vector<Token>& tokens)
{
	m_tokens = std::move(tokens);
}

int TokenizedShader::FindToken(TokenType type, unsigned int offset)
{
	for (int i = offset; i < m_tokens.size(); i++)
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

int TokenizedShader::FindHint(std::string hintCommand, std::string hintArgument, unsigned int offset)
{
	for (int i = offset; i < m_tokens.size(); i++)
	{
		if (m_tokens[i].Type == TokenType::HintCommand && m_tokens[i].Text == hintCommand)
		{
			if (m_tokens[i + 1].Type == TokenType::HintArgument && m_tokens[i + 1].Text == hintArgument)
				return i;
		}
	}

	return -1;
}
