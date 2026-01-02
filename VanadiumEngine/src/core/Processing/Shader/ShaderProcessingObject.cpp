#include "pch.h"
#include "ShaderProcessingObject.h"

// TODO: this function is not fully precise but works for now
void Vanadium::Detail::ShaderProcessingObject::Replace(u32 firstToken, u32 endToken, const ShaderProcessingObject& other)
{
	Source.replace(
		Tokenized.Tokens()[firstToken].SourceIndex,
		Tokenized.Tokens()[endToken].SourceIndex - Tokenized.Tokens()[firstToken].SourceIndex,
		other.Source
	);
	Tokenized.Replace(firstToken, endToken, other.Tokenized);
}