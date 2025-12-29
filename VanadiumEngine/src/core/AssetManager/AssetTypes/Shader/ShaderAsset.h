#pragma once
#include "pch.h"
#include "core/Rendering/Shaders/Shader.h"
#include "core/AssetManager/FileAsset.h"
#include "core/Processing/Shader/ShaderProcessingObject.h"

namespace Vanadium
{
	struct ShaderCodeAsset
	{
		ShaderCodeAsset(std::filesystem::path path);

		Detail::ShaderProcessingObject processingObject;

		std::optional<Shader> CreateShader();
	};
}