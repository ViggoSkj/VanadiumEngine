#include "pch.h"
#include "TokenizedShader.h"
#include "core/Processing/Shader/ShaderKeywordMaps.h"

namespace Vanadium::Detail
{
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

	i32 TokenizedShader::FindHint(std::string hintCommand, unsigned int offset)
	{
		for (int i = offset; i < m_tokens.size(); i++)
		{
			if (m_tokens[i].Type == TokenType::HintCommand && m_tokens[i].Text == hintCommand)
			{
				if (m_tokens[i + 1].Type == TokenType::HintArgument)
					return i;
			}
		}

		return -1;
	}
	void TokenizedShader::Replace(u32 begin, u32 end, const TokenizedShader& other)
	{
		u32 beforeBeginIndex = begin == 0 ? 0 : m_tokens[begin].SourceIndex;
		u32 beforeBeingLine = end == 0 ? 0 : m_tokens[begin - 1].SourceLine;

		u32 removedChars = m_tokens[end].SourceIndex - beforeBeginIndex;
		
		u32 otherLineCount = other.m_tokens.back().SourceLine + 1;
		u32 otherCharCount = other.m_tokens.back().SourceIndex + other.m_tokens.back().Text.size();

		for (u32 i = end; i < m_tokens.size(); i++)
		{
			m_tokens[i].SourceLine += otherLineCount;
			m_tokens[i].SourceIndex += otherCharCount - removedChars;
		}

		m_tokens.erase(m_tokens.begin() + begin, m_tokens.begin() + end);

		m_tokens.insert(m_tokens.begin() + begin, other.Tokens().begin(), other.Tokens().end());

		for (u32 i = begin; i < begin + other.Tokens().size(); i++)
		{
			m_tokens[i].SourceIndex += beforeBeginIndex + 1;
			m_tokens[i].SourceLine += beforeBeingLine;
		}
	}
}