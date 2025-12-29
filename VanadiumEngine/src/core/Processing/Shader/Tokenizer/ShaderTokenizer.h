#pragma once
#include "pch.h"
#include "ShaderToken.h"
#include "TokenizedShader.h"

namespace Vanadium::Detail
{
	class Tokenizer
	{
	public:
		static TokenizedShader Tokenize(std::string source);

	private:
		Tokenizer(std::string source);

		void Tokenize();

		void TokenizeEnd();
		void TokenizeUniOperator();
		void TokenizeOperator(std::string op);
		void TokenizeFlowControl();
		void TokenizeKeyword(std::string keyword);
		void TokenizeDataType(std::string type);
		bool validNameChar(char c, char prev, char next);
		void TokenizeHint();
		void AddToken(TokenType type, std::string text, unsigned int sourceIndex);
		void AddToken(TokenType type, std::string text);
		void AddToken(TokenType type, char c, unsigned int sourceIndex);
		void AddToken(TokenType type, char c);
		unsigned int LineNumber(unsigned int cursorPosition);
		std::string CursorWord();

		std::vector<Token> m_tokens;
		unsigned int m_cursor = 0;
		std::string m_source;
	};
}
