#pragma once

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
	unsigned int SourceIndex;
	unsigned int SourceLine;

	Token()
		: Type(TokenType::Empty), Text(""), SourceIndex(0), SourceLine(0) {
	};

	Token(TokenType type, std::string text, unsigned int sourceIndex, unsigned int sourceLine)
		: Type(type), Text(text), SourceIndex(sourceIndex), SourceLine(sourceLine) {
	};
};
