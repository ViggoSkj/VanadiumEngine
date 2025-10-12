#pragma once
#include "Tokenizer/TokenizedShader.h"
#include "Tokenizer/ShaderTokenizer.h"

struct ShaderProcessingObject
{
	ShaderProcessingObject(std::string source)
		: Source(source), Tokenized(Tokenizer::Tokenize(source)) { }

	ShaderProcessingObject(std::string source, TokenizedShader tokenizedShader)
		: Source(source), Tokenized(tokenizedShader) {
	}

	TokenizedShader Tokenized;
	std::string Source;
};