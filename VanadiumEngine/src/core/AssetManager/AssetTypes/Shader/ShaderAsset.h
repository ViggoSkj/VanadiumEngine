#pragma once
#include "pch.h"
#include "core/Rendering/Shaders/Shader.h"
#include "core/AssetManager/FileAsset.h"
#include "core/Processing/Shader/ShaderProcessingObject.h"

namespace Vanadium
{
	class ShaderCodeAsset
	{
	public:
		static std::shared_ptr<ShaderCodeAsset> LoadFromFile(std::filesystem::path path);

		std::vector<UniformObjectDescriptor> GetUniformObjectDescriptors();
		std::optional<ShaderDescriptor> CreateShaderDescriptor();
		std::optional<Shader> CreateShader();
		Detail::ShaderProcessingObject m_processingObject;
	};
}