#include "ShaderAsset.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"

ShaderAsset::ShaderAsset(std::string filePath)
	: ShaderProgram(FileAsset::ReadFile(filePath)) {

};