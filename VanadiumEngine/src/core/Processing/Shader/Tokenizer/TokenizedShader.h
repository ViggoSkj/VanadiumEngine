#pragma once
#include <vector>
#include "ShaderToken.h"
#include "core/Processing/Shader/ShaderKeyword.h"
#include "core/Rendering/Shaders/ShaderDataType.h"

class TokenizedShader
{
public:
	TokenizedShader(std::vector<Token>& tokens);

	int FindToken(TokenType type, unsigned int offset = 0);
	int FindKeyword(ShaderKeyword keyword, unsigned int offset = 0);
	int FindHint(std::string hintCommand, std::string hintArgument, unsigned int offset = 0);

	const std::vector<Token>& Tokens() {
		return m_tokens;
	};

private:
	std::vector<Token> m_tokens;
};