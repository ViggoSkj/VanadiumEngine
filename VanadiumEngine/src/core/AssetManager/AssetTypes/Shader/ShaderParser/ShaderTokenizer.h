#pragma once
#include <string>
#include <vector>

enum TokenType
{
	Empty,
	Name,
	Type,
	Number,
	Keyword,
	End,
	FlowControl,
	HintCommand,
	HintArgument,
	Operator,
};

enum ShaderKeyword
{
	Layout,
	In,
	Uniform,
	Location,
};

struct Token
{
	TokenType Type;
	std::string Text;

	Token()
		: Type(TokenType::Empty), Text("") {
	};

	Token(TokenType type, std::string text)
		: Type(type), Text(text) {
	};
};


class Tokenizer
{
public:
	Tokenizer(std::string source);

	int FindToken(TokenType type, unsigned int offset = 0);
	int FindKeyword(ShaderKeyword keyword, unsigned int offset = 0);
	const std::vector<Token>& Tokens() { return m_tokens; }

private:
	void Tokenize();

	void TokenizeEnd();
	void TokenizeUniOperator();
	void TokenizeFlowControl();
	void TokenizeKeyword(ShaderKeyword keyword);
	void TokenizeDataType(std::string type);
	std::string CursorName();
	bool validNameChar(char c);
	void TokenizeHint();
	void AddToken(TokenType type, std::string text);
	void AddToken(TokenType type, char c);
	Token LastToken();

	std::vector<Token> m_tokens;
	unsigned int m_cursor = 0;
	std::string m_source;
};

void TokenizeShaderSource(std::string source);
