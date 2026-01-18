#include "pch.h"
#include <iostream>
#include "StyleSheetParser.h"

static bool IsValidCharacter(char c)
{
	return IsOperationalCharacter(c) ||
		IsWhiteSpaceCharacter(c) ||
		IsPartiallyNameCharacter(c) ||
		IsPartialyNumericCharacter(c);
}

static bool IsFullyNumericCharacter(char c)
{
	return '0' <= c && c <= '9';
}

static bool IsPartialyNumericCharacter(char c)
{
	return IsFullyNumericCharacter(c) || c == '.';
}

static bool IsOperationalCharacter(char c)
{
	return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
		c == ';' || c == ':' || c == ',' ||
		c == '.' || c == '#';
}

static bool IsWhiteSpaceCharacter(char c)
{
	// TODO: impl all whitespace
	return c == ' ' || c == '\n' || c == '\t';
}

static bool IsFullyNameCharacter(char c)
{
	return ('A' <= c && c <= 'z') || c == '_';
}

static bool IsPartiallyNameCharacter(char c)
{
	return IsFullyNameCharacter(c) || ('0' <= c && c <= '9');
}

std::optional<TokenizedStyleSheet> TokenizedStyleSheet::TokenizeStyleSheet(std::string_view source)
{
	// validate chars
	bool failed = false;

	for (i32 i = 0; i < source.size(); i++)
	{
		if (!IsValidCharacter(source[i]))
		{
			failed = true;
			break;
		}
	}

	if (failed)
		return std::nullopt;

	// tokenize
	std::vector<ParsedStyleSheetToken> tokens;

	i32 cursor = 0; // where we are processing from, everything behind is irrelevant
	i32 view = 0; // current reading position to detirmine the length

	while (cursor < source.size())
	{
		if (failed)
			break;

		if (cursor > view)
			view = cursor;
#define CURSOR_CHAR source[cursor]
#define VIEW_CHAR source[view]

		if (cursor == view)
		{
			if (IsWhiteSpaceCharacter(CURSOR_CHAR))
				cursor++;
			else
				view++;
		}
		else
		{
			if (IsFullyNameCharacter(CURSOR_CHAR))
			{
				if (IsPartiallyNameCharacter(VIEW_CHAR))
				{
					// continue grabbing name
					view++;
				}
				else
				{
					// name found
					tokens.push_back(ParsedStyleSheetToken(cursor, view));
					cursor = view;
				}
			}
			else if (IsOperationalCharacter(CURSOR_CHAR))
			{
				if (IsOperationalCharacter(VIEW_CHAR))
				{
					// continue grabing operator
					view++;
				}
				else
				{
					// operation found
					tokens.push_back(ParsedStyleSheetToken(cursor, view));
					cursor = view;
				}
			}
			else if (IsFullyNumericCharacter(CURSOR_CHAR))
			{
				if (IsPartialyNumericCharacter(VIEW_CHAR))
				{
					// continue grabbing numeric chars
					view++;
				}
				else
				{
					// numeric value found
					tokens.push_back(ParsedStyleSheetToken(cursor, view));
					cursor = view;
				}
			}
			else
			{
				failed = true;
			}
		}
	}

	if (failed)
		return std::nullopt;

	TokenizedStyleSheet sheet;
	sheet.Tokens = tokens;
	return sheet;
}

std::optional<StyleSheetParser> StyleSheetParser::Parse(std::string_view source)
{
	std::optional<TokenizedStyleSheet> tokenized = TokenizedStyleSheet::TokenizeStyleSheet(source);
	if (!tokenized.has_value())
		return std::nullopt;

	StyleSheetParser parser;
	parser.m_tokens = tokenized.value();

	if (!parser.ValidateDepth())
		return std::nullopt;

	return parser;
}

std::string_view StyleSheetParser::Token(i32 index)
{
	return m_source.substr(m_tokens.Tokens[index].sourceStart, m_tokens.Tokens[index].sourceEnd - m_tokens.Tokens[index].sourceStart);
}

bool StyleSheetParser::ValidateDepth()
{
	i32 depth = 0;

	for (i32 i = 0; i < m_tokens.Tokens.size(); i++)
	{
		if (Token(i) == "{")
			depth++;
		else if (Token(i) == "}")
			depth--;

		if (depth < 0 || depth > 1)
			return false;
	}

	return depth == 0;
}