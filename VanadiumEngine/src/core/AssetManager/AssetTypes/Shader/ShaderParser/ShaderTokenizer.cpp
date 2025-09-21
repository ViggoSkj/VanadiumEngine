#include "ShaderTokenizer.h"
#include "../ShaderDataTypeMaps.h"
#include "../ShaderDataType.h"
#include <string>
#include <vector>
#include <map>

const char* KeywordString(ShaderKeyword keyword)
{
	switch (keyword)
	{
	case Layout:
		return "layout";
	case In:
		return "in";
	case Uniform:
		return "uniform";
	case Location:
		return "location";
	default:
		throw "e";
	}
}

size_t KeywordLength(ShaderKeyword keyword)
{
	return strlen(KeywordString(keyword));
}

Tokenizer::Tokenizer(std::string source)
	: m_source(source)
{
	Tokenize();
};

int Tokenizer::FindToken(TokenType type, unsigned int offset)
{
	for (int i = 0; i < m_tokens.size(); i++)
	{
		if (m_tokens[i].Type == type)
			return i;
	}

	return -1;
}

int Tokenizer::FindKeyword(ShaderKeyword keyword, unsigned int offset)
{
	for (int i = offset; i < m_tokens.size(); i++)
	{
		if (m_tokens[i].Type == TokenType::Keyword && m_tokens[i].Text == KeywordString(keyword))
			return i;
	}

	return -1;
}

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
		for (ShaderKeyword keyword : usedKeywords)
		{
			if (KeywordString(keyword) == cursorName)
			{
				TokenizeKeyword(keyword);
				progress = true;
				break;
			}
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

void Tokenizer::TokenizeKeyword(ShaderKeyword keyword)
{
	AddToken(TokenType::Keyword, KeywordString(keyword));
	m_cursor += KeywordLength(keyword);
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

Token Tokenizer::LastToken()
{
	if (m_tokens.size() < 1)
		return Token();
	return m_tokens.back();
}

void TokenizeShaderSource(std::string source)
{
	Tokenizer tokenizer(source);

	// find vertex info

	const std::vector<Token>& tokens = tokenizer.Tokens();

	unsigned int cursor = -1;

	while ((cursor = tokenizer.FindKeyword(ShaderKeyword::In, cursor + 1)) != -1)
	{
		Token typeToken = tokens[cursor + 1];
		Token locationToken = tokens[cursor - 2];

		unsigned int location = std::stoi(locationToken.Text);
		ShaderDataType type = StringToShaderDataType.at(typeToken.Text);
	}
}