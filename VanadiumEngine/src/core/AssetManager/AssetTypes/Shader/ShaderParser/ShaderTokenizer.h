#pragma once
#include <string>
#include <vector>
#include "ShaderToken.h"
#include "TokenizedShader.h"

class Tokenizer
{
public:
	static TokenizedShader Tokenize(std::string source);

private:
	Tokenizer(std::string source);

	void Tokenize();

	void TokenizeEnd();
	void TokenizeUniOperator();
	void TokenizeFlowControl();
	void TokenizeKeyword(std::string keyword);
	void TokenizeDataType(std::string type);
	bool validNameChar(char c);
	void TokenizeHint();
	void AddToken(TokenType type, std::string text);
	void AddToken(TokenType type, char c);
	std::string CursorName();

	std::vector<Token> m_tokens;
	unsigned int m_cursor = 0;
	std::string m_source;
};
