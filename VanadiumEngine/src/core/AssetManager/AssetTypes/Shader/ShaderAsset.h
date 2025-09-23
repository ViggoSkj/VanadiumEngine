#pragma once
#include "core/AssetManager/AssetTypes/Shader/ShaderDescriptor.h"
#include "core/rendering/Shaders/GLShader.h"
#include "../../FileAsset.h"

struct ShaderAsset : public FileAsset
{
	ShaderAsset(std::string source);

	ShaderDescriptor Descriptor;
	GLShader Shader;
};
