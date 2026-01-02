#pragma once
#include "core/CoreTypes.h"
#include "ShaderToken.h"
#include "core/Processing/Shader/ShaderKeyword.h"
#include "core/Rendering/Shaders/ShaderDataType.h"

namespace Vanadium::Detail
{
	class TokenizedShader
	{
	public:
		TokenizedShader() = default;
		TokenizedShader(std::vector<Token>& tokens);

		int FindToken(TokenType type, unsigned int offset = 0);
		int FindKeyword(ShaderKeyword keyword, unsigned int offset = 0);
		int FindHint(std::string hintCommand, std::string hintArgument, unsigned int offset = 0);
		i32 FindHint(std::string hintCommand, unsigned int offset = 0);

		void Replace(u32 begin, u32 end, const TokenizedShader& other);

		const std::vector<Token>& Tokens() const {
			return m_tokens;
		};

	private:
		std::vector<Token> m_tokens;
	};
}