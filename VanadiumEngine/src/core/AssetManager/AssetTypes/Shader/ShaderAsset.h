#pragma once
#include "pch.h"
#include "Shaders/Shader.h"
#include "FileAsset.h"
#include "core/Processing/Shader/ShaderProcessingObject.h"

template<typename TFileAsset>
class FileAssetStore;

struct ShaderCodeAsset
{
	ShaderCodeAsset(std::filesystem::path path);

	ShaderProcessingObject processingObject;

	Shader CreateShader();
};