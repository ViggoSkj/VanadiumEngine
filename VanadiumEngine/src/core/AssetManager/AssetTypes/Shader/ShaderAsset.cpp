#include "pch.h"
#include "ShaderAsset.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"
#include "core/Processing/Shader/CodeGenerator/ShaderCodeGenerator.h"
#include "core/Application.h"
#include "core/Processing/Shader/IShaderCodeLoader.h"


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

Shader ShaderCodeAsset::CreateShader()
{
	ShaderDescriptor desc(processingObject.Tokenized);
	Shader shader = Shader(processingObject.Source, desc);
	return shader;
}