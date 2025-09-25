#include "ShaderAsset.h"
#include "core/Proccessing/Shader/ShaderTokenizer.h"

ShaderAsset::ShaderAsset(std::string filePath)
	: ShaderProgram(FileAsset::ReadFile(filePath)) {

};