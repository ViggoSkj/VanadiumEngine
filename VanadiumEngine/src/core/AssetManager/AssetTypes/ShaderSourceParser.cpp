#include "ShaderSourceObject.h"
#include <string>
#include <vector>
#include <map>

enum DataType
{
	Void,
	Bool,
	Int,
	UInt,
	Float,
	Double,
	Mat4x4,
};

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

const char* KeywordString(ShaderKeyword keyword)
{
	switch (keyword)
	{
	case Layout:
		return "layout";
	case In:
		return "in";
	case Uniform:
		return "uniform";
	case Location:
		return "location";
	default:
		throw "e";
	}
}

size_t KeywordLength(ShaderKeyword keyword)
{
	return strlen(KeywordString(keyword));
}

const char* TypeString(DataType type)
{
	switch (type)
	{
	case Void:
		return "void";
	case Bool:
		return "bool";
	case Int:
		return "int";
	case UInt:
		return "uint";
	case Float:
		return "float";
	case Double:
		return "double";
	case Mat4x4:
		return "mat4x4";
	default:
		throw "e";
	}
}

size_t TypeLength(DataType type)
{
	return strlen(TypeString(type));
}

static std::map<const char*, DataType> STRING_TO_TYPE
{
	{"bool", DataType::Bool},
	{"int", DataType::Int},
	{"uint", DataType::UInt},
	{"float", DataType::Float},
	{"double", DataType::Double},
	{"mat4", DataType::Mat4x4},
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
	Tokenizer(std::string source)
		: m_source(source)
	{
		Tokenize();
	};

	void Tokenize()
	{
		std::vector<ShaderKeyword> usedKeywords = {
			ShaderKeyword::Layout,
			ShaderKeyword::Uniform,
			ShaderKeyword::In,
			ShaderKeyword::Location,
		};

		std::vector<DataType> usedTypes = {
			DataType::Void,
			DataType::Bool,
			DataType::Int,
			DataType::UInt,
			DataType::Float,
			DataType::Double,
			DataType::Mat4x4,
		};

		while (m_cursor < m_source.size())
		{
			const char cursorChar = m_source[m_cursor];
			std::string cursorName = CursorName();

			bool progress = true;

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
				TokenizeUniOperator();
				break;
			default:
				progress = false;
				break;
			}

			if (progress)
				continue;

			// check for keyowrds
			for (ShaderKeyword keyword : usedKeywords)
			{
				if (KeywordString(keyword) == cursorName)
				{
					TokenizeKeyword(keyword);
					progress = true;
					break;
				}
			}

			if (progress)
				continue;

			// check for types
			for (DataType type : usedTypes)
			{
				if (TypeString(type) == cursorName)
				{
					TokenizeDataType(type);
					progress = true;
					break;
				}
			}

			if (progress)
				continue;

			AddToken(TokenType::Name, cursorName);
			m_cursor += cursorName.size();
		}
	}


	void TokenizeEnd()
	{
		AddToken(TokenType::End, ';');
		m_cursor++;
	}

	void TokenizeUniOperator()
	{
		AddToken(TokenType::Operator, m_source[m_cursor]);
		m_cursor++;
	}

	void TokenizeFlowControl()
	{
		AddToken(TokenType::FlowControl, m_source[m_cursor]);
		m_cursor++;
	}

	void TokenizeKeyword(ShaderKeyword keyword)
	{
		AddToken(TokenType::Keyword, KeywordString(keyword));
		m_cursor += KeywordLength(keyword);
	}

	void TokenizeDataType(DataType dataType)
	{
		AddToken(TokenType::Keyword, TypeString(dataType));
		m_cursor += TypeLength(dataType);
	}

	std::string CursorName()
	{
		std::string cursorName = "";

		for (int i = 0; validNameChar(m_source[m_cursor + i]); i++)
		{
			cursorName.push_back(m_source[m_cursor + i]);
		}

		return cursorName;
	}

	bool validNameChar(char c)
	{
		if (c >= '0' && c <= '9') return true;
		if (c >= 'A' && c <= 'Z') return true;
		if (c >= 'a' && c <= 'z') return true;
		if (c == '_') return true;
		return false;
	}


	void TokenizeHint()
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

	void AddToken(TokenType type, std::string text)
	{
		m_tokens.push_back(Token(type, text));
	}

	void AddToken(TokenType type, char c)
	{
		std::string text(1, c);
		AddToken(type, text);
	}

	Token LastToken()
	{
		if (m_tokens.size() < 1)
			return Token();
		return m_tokens.back();
	}

private:
	std::vector<Token> m_tokens;
	unsigned int m_cursor = 0;
	std::string m_source;
};

void TokenizeShaderSource(std::string source)
{
	Tokenizer tokenizer(source);

	// find vertex info


}