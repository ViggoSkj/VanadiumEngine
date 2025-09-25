#pragma once
#include "Shaders/Shader.h"
#include "FileAsset.h"

struct ShaderAsset : public FileAsset
{
	ShaderAsset(std::string source);
	
	Shader ShaderProgram;
};
