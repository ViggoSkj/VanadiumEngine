#include "pch.h"
#include "ShaderAsset.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"
#include "core/Processing/Shader/CodeGenerator/ShaderCodeGenerator.h"
#include "core/Application.h"
#include "core/Processing/Shader/IShaderCodeLoader.h"

using Vanadium::Application;

struct ShaderCodeAssetLoader : public IShaderCodeLoader
{
	ShaderProcessingObject* LoadShaderCode(std::filesystem::path path) override
	{
		FileAssetStore<ShaderCodeAsset>* store = Application::Get().GetAssetManager()->GetAssetStore<ShaderCodeAsset>();
		return &store->GetAsset(path)->processingObject;
	}
};

ShaderCodeAsset::ShaderCodeAsset(std::filesystem::path path)
	: processingObject(FileAsset::ReadFile(path))
{
	ShaderCodeAssetLoader loader;
	ShaderCodeGenerator::ExecuteIncludes(processingObject, &loader);
}

std::optional<Shader> ShaderCodeAsset::CreateShader()
{
	std::optional<ShaderDescriptor> created = ShaderDescriptor::Create(processingObject.Tokenized);

	if (!created.has_value())
	{
		return std::nullopt;
	}

	return Shader::CreateShader(processingObject.Source, created.value());
}