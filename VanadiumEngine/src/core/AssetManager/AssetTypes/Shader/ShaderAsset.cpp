#include "ShaderAsset.h"
#include "ShaderParser/ShaderTokenizer.h"

ShaderAsset::ShaderAsset(std::string source)
	: Descriptor(Tokenizer::Tokenize(FileAsset::ReadFile(source)))
{
	Shader.LoadSource(source.c_str());
}
