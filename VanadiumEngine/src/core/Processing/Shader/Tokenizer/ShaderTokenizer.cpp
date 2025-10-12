#include "pch.h"
#include "ShaderTokenizer.h"


#include "core/Processing/Shader/ShaderKeyword.h"
#include "core/Processing/Shader/ShaderKeywordMaps.h"
#include "Shaders/ShaderDataTypeMaps.h"
#include "Shaders/ShaderDataType.h"
#include "TokenizedShader.h"
#include "core/Processing/Shader/ShaderOperator.h"

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

	int i = 0;
	while (m_cursor < m_source.size())
	{
		const char cursorChar = m_source[m_cursor];
		std::string cursorWord = CursorWord();

		bool progress = true;

		if (i > 100000)
		{
			throw "to many iterations, somethings wrong";
		}
		i++;

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
		case '%':
			TokenizeUniOperator();
			break;
		default:
			progress = false;
			break;
		}

		if (progress)
			continue;

		// check for operator
		if (StringToShaderOperator.contains(cursorWord))
		{
			TokenizeOperator(cursorWord);
			progress = true;
		}

		if (progress)
			continue;

		// check for keyowrds
		if (StringToShaderKeyword.contains(cursorWord))
		{
			TokenizeKeyword(cursorWord);
			progress = true;
		}

		if (progress)
			continue;

		// check for types
		if (StringToShaderDataType.contains(cursorWord))
		{
			TokenizeDataType(cursorWord);
			progress = true;
		}
		
		if (progress)
			continue;

		AddToken(TokenType::Name, cursorWord);
		m_cursor += cursorWord.size();
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

void Tokenizer::TokenizeOperator(std::string op)
{
	AddToken(TokenType::Operator, op);
	m_cursor += op.size();
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
	AddToken(TokenType::Type, type);
	m_cursor += type.size();
}

std::string Tokenizer::CursorWord()
{
	std::string cursorName = "";

	char prev = '\0';
	char next = '\0';

	int i = 0;
	while (true)
	{
		if (i + m_cursor > 0)
			prev = m_source[m_cursor + i - 1];

		if (i + m_cursor + 1 < m_source.size())
			next = m_source[m_cursor + i + 1];

		if (!validNameChar(m_source[m_cursor + i], prev, next))
			break;

		cursorName.push_back(m_source[m_cursor + i]);
		
		i++;
	}

	return cursorName;
}

bool Tokenizer::validNameChar(char c, char prev, char next)
{
	if (c >= '0' && c <= '9') return true;
	if (c >= 'A' && c <= 'Z') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c == '_') return true;

	if (c == '|')
		return (prev == '|' ? 1 : 0 + next == '|' ? 1 : 0) == 1;
	if (c == '&')
		return (prev == '&' ? 1 : 0 + next == '&' ? 1 : 0) == 1;
	if (c == '=')
		return (prev == '=' ? 1 : 0 + next == '=' ? 1 : 0) == 1;
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
void Tokenizer::AddToken(TokenType type, std::string text, unsigned int sourceIndex)
{
	m_tokens.push_back(Token(type, text, sourceIndex, LineNumber(sourceIndex)));
}

void Tokenizer::AddToken(TokenType type, std::string text)
{
	m_tokens.push_back(Token(type, text, m_cursor, LineNumber(m_cursor)));
}

void Tokenizer::AddToken(TokenType type, char c, unsigned int sourceIndex)
{
	std::string text(1, c);
	AddToken(type, text, sourceIndex);
}

void Tokenizer::AddToken(TokenType type, char c)
{
	std::string text(1, c);
	AddToken(type, text);
}

unsigned int Tokenizer::LineNumber(unsigned int cursorPosition)
{
	unsigned int lineNumber = 0;
	for (int i = cursorPosition; i > 0; i--)
	{
		if (m_source[cursorPosition] == '\n')
			lineNumber++;
	}
	return lineNumber;
}
