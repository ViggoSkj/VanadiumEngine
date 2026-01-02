#pragma once
#include "Tokenizer/TokenizedShader.h"
#include "Tokenizer/ShaderTokenizer.h"

namespace Vanadium::Detail
{
	struct ShaderProcessingObject
	{
		ShaderProcessingObject(std::string source)
			: Source(source), Tokenized(Tokenizer::Tokenize(source)) {
		}

		ShaderProcessingObject(std::string source, TokenizedShader tokenizedShader)
			: Source(source), Tokenized(tokenizedShader) {
		}

		void Replace(u32 firstToken, u32 endToken, const ShaderProcessingObject& other);

		TokenizedShader Tokenized;
		std::string Source;
	};
}