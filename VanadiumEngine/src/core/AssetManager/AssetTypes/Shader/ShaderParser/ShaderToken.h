#pragma once
#include <string>

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
