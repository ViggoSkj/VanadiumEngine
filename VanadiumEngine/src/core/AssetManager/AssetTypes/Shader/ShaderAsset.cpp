#include "pch.h"
#include "ShaderAsset.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"
#include "core/Processing/Shader/CodeGenerator/ShaderCodeGenerator.h"
#include "core/Application.h"

#include "core/Processing/Shader/IShaderCodeLoader.h"
#include "core/Processing/Shader/Tokenizer/TokenAnalyzer.h"

namespace Vanadium
{
	using Vanadium::Application;

	struct ShaderCodeAssetLoader : public Detail::IShaderCodeLoader
	{
		Detail::ShaderProcessingObject* LoadShaderCode(std::filesystem::path path) override
		{
			FileAssetStore<ShaderCodeAsset>* store = Application::Get().GetAssetManager()->GetAssetStore<ShaderCodeAsset>();
			return &store->GetAsset(path)->m_processingObject;
		}
	};

	std::shared_ptr<ShaderCodeAsset> ShaderCodeAsset::LoadFromFile(std::filesystem::path path)
	{
		std::expected<std::string, ErrorValue> data = Vanadium::Detail::ReadFile(path);
		if (!data)
			return nullptr;

		Detail::ShaderProcessingObject processingObject(data.value());
		
		ShaderCodeAssetLoader loader;
		Detail::ShaderCodeGenerator::ExecuteIncludes(processingObject, &loader);
		std::shared_ptr<ShaderCodeAsset> asset = std::make_shared<ShaderCodeAsset>();
		asset->m_processingObject = processingObject;
		return asset;
	}

	std::vector<UniformObjectDescriptor> ShaderCodeAsset::GetUniformObjectDescriptors()
	{
		std::vector<UniformObjectDescriptor> descs;
		Vanadium::Detail::TokenAnalyzer::GetUniformObjects(m_processingObject.Tokenized, descs);
		return descs;
	}

	std::optional<ShaderDescriptor> ShaderCodeAsset::CreateShaderDescriptor()
	{
		return ShaderDescriptor::Create(m_processingObject.Tokenized);
	}

	std::optional<Shader> ShaderCodeAsset::CreateShader()
	{
		std::optional<ShaderDescriptor> created = ShaderDescriptor::Create(m_processingObject.Tokenized);

		if (!created.has_value())
			return std::nullopt;

		std::optional<Shader> shaderOpt = Shader::CreateShader(m_processingObject.Source, created.value());

		if (!shaderOpt.has_value())
			return std::nullopt;

		Shader shader = shaderOpt.value();
		// auto bind ubos;

		RenderingManager& man = *Application::Get().GetRenderingManager();

		for (auto desc : shader.Descriptor().VertexShader.UniformObjects)
		{
			UniformObject* object = man.FindUniformObject(desc.Name);
			if (object == nullptr)
				continue;

			shader.TryUseUniformObject(*object, ShaderType::VertexShader);
		}

		for (auto desc : shader.Descriptor().FragmentShader.UniformObjects)
		{
			UniformObject* object = man.FindUniformObject(desc.Name);
			if (object == nullptr)
				continue;

			shader.TryUseUniformObject(*object, ShaderType::FragmentShader);
		}

		return shader;
	}
}