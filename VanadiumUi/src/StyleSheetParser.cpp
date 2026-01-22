#include "pch.h"
#include <iostream>
#include "StyleSheetParser.h"
#include "core/util/StringHash.h"

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
	TokenAnalyzer(const TokenizedStyleSheet& tokens, i32 start)
		: tokens(tokens), cursor(start), view(start)
	{

	}

	const ParsedStyleSheetToken& Cursor() const { return tokens.tokens[cursor]; }
	const ParsedStyleSheetToken& View() const { return tokens.tokens[view]; }
	std::string_view CurrentCursor() const { return tokens.Token(cursor); }
	std::string_view CurrentView() const { return tokens.Token(view); }
	size_t Count() const { return tokens.tokens.size(); };

	i32 view;
	i32 cursor;
	const TokenizedStyleSheet& tokens;

private:
	i32 m_savePoint;
};


#pragma region Parsing

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

static struct StyleDefinitionTarget
{
	std::string name;
	StyleSourceType type = StyleSourceType::None;
};

static struct StyleSheetPropertyValue
{
	std::vector<float> numbers;
};

static struct StyleSheetProperty
{
	std::string_view property;
	StyleSheetPropertyValue value;
};

static struct StyleDefinition
{
	StyleDefinitionTarget target;
	std::shared_ptr<StyleDefinition> parentScope;
	std::vector<StyleSheetProperty> properties;
};

StyleSourceType TokenToOwnerType(std::string_view token)
{
	if (token == ".")
		return StyleSourceType::Class;
	if (token == "#")
		return StyleSourceType::Id;
	return StyleSourceType::None;
}

std::optional<StyleSheetPropertyValue> ParsePropertyValue(TokenizedStyleSheet tokenized, TokenAnalyzer& ana)
{
	StyleSheetPropertyValue value;

	while (ana.cursor < ana.Count() && ana.CurrentCursor() != ";")
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

std::expected<std::vector<StyleDefinition>, ErrorValue> CreateScopes(TokenizedStyleSheet tokenized, std::shared_ptr<StyleDefinition> parentScope)
{
	std::vector<StyleDefinition> scopes;
	StyleDefinition* scope = nullptr;

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

		switch (state)
		{
		case SearchingForOwnerType:
		{
			std::string_view s = TOKEN_STR;
			StyleSourceType type = TokenToOwnerType(TOKEN_STR);
			if (type == StyleSourceType::None)
				return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Unexpected owner type."));
			scopes.push_back(StyleDefinition());
			scope = &scopes.back();
			scope->parentScope = parentScope;
			scope->target.type = type;
			state = SearchingForOwner;
			i++;
			break;
		}
		case SearchingForOwner:
		{
			if (TOKEN.type != StyleSheetTokenType::Name)
				return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Invalid owner name."));
			scope->target.name = TOKEN_STR;
			state = OpeningScope;
			i++;
			break;
		}
		case OpeningScope:
		{
			if (TOKEN_STR != "{")
				return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Scope needs to be opend with a \"{\"."));
			state = FindingPropertyName;
			i++;
			break;
		}
		case FindingPropertyName:
		{
			if (TOKEN.type != StyleSheetTokenType::Name)
				return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Invalid property name."));
			scope->properties.emplace_back();
			scope->properties.back().property = TOKEN_STR;
			i++;
			if (TOKEN_STR != ":")
				return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Property definition needs a \":\"."));
			i++;

			state = FindingPropertyValue;

			break;
		}
		case FindingPropertyValue:
		{
			TokenAnalyzer analyzer(tokenized, i);
			std::optional<StyleSheetPropertyValue> valueOpt = ParsePropertyValue(tokenized, analyzer);
			if (!valueOpt.has_value())
				return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Invalid property value."));
			scope->properties.back().value = valueOpt.value();

			i = analyzer.cursor;

			if (TOKEN_STR != ";")
				return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Property definition needs to end with a \";\"."));
			i++;
			if (TOKEN_STR == "}")
			{
				i++;
				state = SearchingForOwnerType;
			}
			else
				state = FindingPropertyName;
			break;
		}
		default:
			return std::unexpected(ErrorValue(StyleSheetParserDomain, InvalidState, "Invalid parser state."));
		}
	}

	return scopes;
}

#pragma endregion

#pragma region StyleResolving

Style ResolveStyle(const std::vector<StyleSheetProperty>& properties)
{
	Style style;

	for (const StyleSheetProperty& p : properties)
	{
		switch (hash_sv(p.property))
		{
		case "border"_id:
		{
			if (p.value.numbers.size() == 1)
				style.border = p.value.numbers[0];

			break;
		}
		default:
			break;
		}
	}

	return style;
}

#pragma endregion StyleResolving

std::expected<StyleSheetParser, ErrorValue> StyleSheetParser::Parse(std::string_view source)
{
	std::optional<TokenizedStyleSheet> tokenized = TokenizedStyleSheet::TokenizeStyleSheet(source);
	if (!tokenized.has_value())
		return std::unexpected(ErrorValue(StyleSheetParserDomain, FailedTokenization));

	StyleSheetParser parser;
	parser.m_tokens = tokenized.value();
	parser.m_source = source;

	if (!parser.ValidateDepth())
		return std::unexpected(ErrorValue(StyleSheetParserDomain, SyntaxError, "Deapth validation failed."));

	std::expected<std::vector<StyleDefinition>, ErrorValue> scopesOpt = CreateScopes(parser.m_tokens, nullptr);

	if (!scopesOpt)
		return std::unexpected(scopesOpt.error());

	std::vector<StyleDefinition> scopes = scopesOpt.value();

	for (const StyleDefinition& def : scopes)
	{
		parser.generated.PushSourcedStyle(SourceTarget(def.target.name, def.target.type), ResolveStyle(def.properties));
	}

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