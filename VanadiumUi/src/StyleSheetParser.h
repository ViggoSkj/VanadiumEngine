#pragma once
#include "Style.h"

struct ParsedStyleSheetToken
{
	ParsedStyleSheetToken(i32 start, i32 end)
		: sourceStart(start), sourceEnd(end)
	{

	}

	i32 sourceStart;
	i32 sourceEnd;
};

struct TokenizedStyleSheet
{
	static std::optional<TokenizedStyleSheet> TokenizeStyleSheet(std::string_view source);

	std::vector<ParsedStyleSheetToken> Tokens;
};

class StyleSheetParser
{
public:
	static std::optional<StyleSheetParser> Parse(std::string_view source);

private:
	std::string_view Token(i32 index);

	bool ValidateDepth();

	TokenizedStyleSheet m_tokens;
	std::string m_source;
};