#include "ShaderTokenizer.h"
#include <string>
#include <vector>
#include "../ShaderKeyword.h"
#include "../ShaderKeywordMaps.h"
#include "../ShaderDataTypeMaps.h"
#include "../ShaderDataType.h"
#include "TokenizedShader.h"

TokenizedShader Tokenizer::Tokenize(std::string source)
{
	Tokenizer tokenizer(source);
	return TokenizedShader(tokenizer.m_tokens);
}

Tokenizer::Tokenizer(std::string source)
	: m_source(source)
{
	Tokenize();
};

void Tokenizer::Tokenize()
{
	std::vector<ShaderKeyword> usedKeywords = {
		ShaderKeyword::Layout,
		ShaderKeyword::Uniform,
		ShaderKeyword::In,
		ShaderKeyword::Location,
	};

	while (m_cursor < m_source.size())
	{
		const char cursorChar = m_source[m_cursor];
		std::string cursorName = CursorName();

		bool progress = true;

		switch (cursorChar)
		{
		case '#':
			TokenizeHint();
			break;
		case ';':
			TokenizeEnd();
			break;
		case '\n':
		case ' ':
			m_cursor++;
			break;
		case '(':
		case ')':
		case '{':
		case '}':
		case ',':
			TokenizeFlowControl();
			break;
		case '+':
		case '-':
		case '/':
		case '*':
		case '=':
		case '.':
			TokenizeUniOperator();
			break;
		default:
			progress = false;
			break;
		}

		if (progress)
			continue;

		// check for keyowrds
		if (StringToShaderKeyword.contains(cursorName))
		{
			TokenizeDataType(cursorName);
			progress = true;
		}

		if (progress)
			continue;

		// check for types
		if (StringToShaderDataType.contains(cursorName))
		{
			TokenizeDataType(cursorName);
			progress = true;
		}
		
		if (progress)
			continue;

		AddToken(TokenType::Name, cursorName);
		m_cursor += cursorName.size();
	}
}

void Tokenizer::TokenizeEnd()
{
	AddToken(TokenType::End, ';');
	m_cursor++;
}

void Tokenizer::TokenizeUniOperator()
{
	AddToken(TokenType::Operator, m_source[m_cursor]);
	m_cursor++;
}

void Tokenizer::TokenizeFlowControl()
{
	AddToken(TokenType::FlowControl, m_source[m_cursor]);
	m_cursor++;
}

void Tokenizer::TokenizeKeyword(std::string keyword)
{
	AddToken(TokenType::Keyword, keyword);
	m_cursor += keyword.size();
}

void Tokenizer::TokenizeDataType(std::string type)
{
	AddToken(TokenType::Keyword, type);
	m_cursor += type.size();
}

std::string Tokenizer::CursorName()
{
	std::string cursorName = "";

	for (int i = 0; validNameChar(m_source[m_cursor + i]); i++)
	{
		cursorName.push_back(m_source[m_cursor + i]);
	}

	return cursorName;
}

bool Tokenizer::validNameChar(char c)
{
	if (c >= '0' && c <= '9') return true;
	if (c >= 'A' && c <= 'Z') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c == '_') return true;
	return false;
}


void Tokenizer::TokenizeHint()
{
	unsigned int end = m_source.find('\n', m_cursor);
	unsigned int endPortion = std::min(end, (unsigned int)m_source.find(' ', m_cursor));

	AddToken(TokenType::HintCommand, m_source.substr(m_cursor, endPortion - m_cursor));

	while (endPortion < end)
	{
		m_cursor = endPortion + 1;
		endPortion = std::min(end, (unsigned int)m_source.find(' ', m_cursor));
		AddToken(TokenType::HintArgument, m_source.substr(m_cursor, endPortion - m_cursor));
	}

	m_cursor = end;
}
void Tokenizer::AddToken(TokenType type, std::string text)
{
	m_tokens.push_back(Token(type, text));
}

void Tokenizer::AddToken(TokenType type, char c)
{
	std::string text(1, c);
	AddToken(type, text);
}