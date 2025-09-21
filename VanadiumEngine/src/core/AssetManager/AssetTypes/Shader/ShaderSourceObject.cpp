#include "ShaderSourceObject.h"
#include "ShaderParser/ShaderTokenizer.h"

ShaderSourceObject::ShaderSourceObject(std::string source)
{
	TokenizedShader shader = Tokenizer::Tokenize(source);
}