#include "pch.h"
#include <iostream>
#include "StyleSheetParser.h"

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

static bool IsValidCharacter(char c)
{
	return IsOperationalCharacter(c) ||
		IsWhiteSpaceCharacter(c) ||
		IsPartiallyNameCharacter(c) ||
		IsPartialyNumericCharacter(c);
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
					tokens.push_back(ParsedStyleSheetToken(cursor, view, StyleSheetTokenType::Name));
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
					tokens.push_back(ParsedStyleSheetToken(cursor, view, StyleSheetTokenType::Logical));
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
					tokens.push_back(ParsedStyleSheetToken(cursor, view, StyleSheetTokenType::Numeric));
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
	sheet.tokens = tokens;
	sheet.source = source;
	return sheet;
}

std::string_view TokenizedStyleSheet::Token(i32 index) const
{
	return source.substr(tokens[index].sourceStart, tokens[index].sourceEnd - tokens[index].sourceStart);
}

class TokenAnalyzer
{
public:
	const ParsedStyleSheetToken& Cursor() const { return tokens.tokens[cursor]; }
	const ParsedStyleSheetToken& View() const { return tokens.tokens[view]; }
	std::string_view CurrentCursor() const { return tokens.Token(cursor); }
	std::string_view CurrentView() const { return tokens.Token(view); }

	i32 view;
	i32 cursor;
	TokenizedStyleSheet tokens;

private:
	i32 m_savePoint;
};


#pragma region Parsing

struct StyleSheetPropertyValue
{
	std::vector<float> numbers;
};

struct StyleSheetProperty
{
	std::string_view property;
	StyleSheetPropertyValue value;
};

enum class PropertyType
{
	None,
	Color,
	Number,
	Vec2,
	Vec3,
	Vec4,
	String
};

enum class ScopeOwnerType
{
	None,
	Class,
	Id
};

struct ScopeOwner
{
	std::string name;
	ScopeOwnerType type;
};

static struct StyleSheetScope
{
	ScopeOwner owner;
	std::shared_ptr<StyleSheetScope> parentScope;
	std::vector<StyleSheetProperty> properties;
};

ScopeOwnerType TokenToOwnerType(std::string_view token)
{
	if (token == ".")
		return ScopeOwnerType::Class;
	if (token == "#")
		return ScopeOwnerType::Id;
	return ScopeOwnerType::None;
}

std::optional<StyleSheetPropertyValue> ParsePropertyValue(TokenizedStyleSheet tokenized, TokenAnalyzer& ana)
{
	StyleSheetPropertyValue value;

	while (ana.CurrentCursor() != ";")
	{
		if (ana.CurrentCursor() == ",")
		{
			ana.cursor++;
		}
		else if (ana.Cursor().type == StyleSheetTokenType::Numeric)
		{
			value.numbers.push_back(std::stof(ana.CurrentCursor().data()));
			ana.cursor++;
		}
	}

	return value;
}

std::optional<StyleSheetScope> CreateScope(TokenizedStyleSheet tokenized, std::shared_ptr<StyleSheetScope> parentScope)
{
	StyleSheetScope scope;
	scope.parentScope = parentScope;

	enum ParserState
	{
		SearchingForOwnerType,
		SearchingForOwner,

		OpeningScope,

		FindingPropertyName,
		FindingPropertyValue,
	};

	ParserState state = ParserState::SearchingForOwnerType;

	i32 i = 0;
	while (i < tokenized.tokens.size())
	{
#define TOKEN_STR tokenized.Token(i)
#define TOKEN tokenized.tokens[i]
#define REQUIRE_STR(str) if (TOKEN_STR != str) return std::nullopt
#define REQUIRE_TYPE(t) if (TOKEN.type != StyleSheetTokenType::t) return std::nullopt

		switch (state)
		{
		case SearchingForOwnerType:
			scope.owner.type = TokenToOwnerType(TOKEN_STR);
			if (scope.owner.type == ScopeOwnerType::None)
				return std::nullopt;
			state = SearchingForOwner;
			i++;
			break;

		case SearchingForOwner:
			REQUIRE_TYPE(Name);
			scope.owner.name = TOKEN_STR;
			state = OpeningScope;
			i++;
			break;

		case OpeningScope:
			REQUIRE_STR("{");
			state = FindingPropertyName;
			i++;
			break;

		case FindingPropertyName:
			REQUIRE_TYPE(Name);
			scope.properties.emplace_back();
			scope.properties.back().property = TOKEN_STR;
			i++;
			REQUIRE_STR(":");
			i++;

			break;

		case FindingPropertyValue:
			TokenAnalyzer analyzer;
			analyzer.cursor = i;
			std::optional<StyleSheetPropertyValue> valueOpt = ParsePropertyValue(tokenized, analyzer);
			if (!valueOpt.has_value())
				return std::nullopt;
			scope.properties.back().value = valueOpt.value();

			i = analyzer.cursor;

			REQUIRE_STR(";");
			i++;
			if (TOKEN_STR == "}")
				state = SearchingForOwnerType;
			else
				state = FindingPropertyName;

		default:
			return std::nullopt;
		}
	}
}

#pragma endregion

std::optional<StyleSheetParser> StyleSheetParser::Parse(std::string_view source)
{
	std::optional<TokenizedStyleSheet> tokenized = TokenizedStyleSheet::TokenizeStyleSheet(source);
	if (!tokenized.has_value())
		return std::nullopt;

	StyleSheetParser parser;
	parser.m_tokens = tokenized.value();
	parser.m_source = source;

	if (!parser.ValidateDepth())
		return std::nullopt;

	return parser;
}

void StyleSheetParser::DebugPrint()
{
	for (i32 i = 0; i < m_tokens.tokens.size(); i++)
	{
		std::cout << m_tokens.Token(i) << std::endl;
	}
}

bool StyleSheetParser::ValidateDepth()
{
	i32 depth = 0;

	for (i32 i = 0; i < m_tokens.tokens.size(); i++)
	{
		if (m_tokens.Token(i) == "{")
			depth++;
		else if (m_tokens.Token(i) == "}")
			depth--;

		if (depth < 0 || depth > 1)
			return false;
	}

	return depth == 0;
}