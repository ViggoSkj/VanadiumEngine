#pragma once
#include "Style.h"

enum class StyleSheetTokenType
{
	Name,
	Logical,
	Numeric
};

struct ParsedStyleSheetToken
{
	ParsedStyleSheetToken(i32 start, i32 end, StyleSheetTokenType type)
		: sourceStart(start), sourceEnd(end), type(type)
	{

	}

	i32 sourceStart;
	i32 sourceEnd;
	StyleSheetTokenType type;
};

struct TokenizedStyleSheet
{
	static std::optional<TokenizedStyleSheet> TokenizeStyleSheet(std::string_view source);

	std::string_view Token(i32 index) const;

	std::vector<ParsedStyleSheetToken> tokens;
	std::string_view source;
};

class StyleSheetParser
{
public:
	static std::optional<StyleSheetParser> Parse(std::string_view source);

	void DebugPrint();
private:

	bool ValidateDepth();

	TokenizedStyleSheet m_tokens;
	std::string m_source;
};