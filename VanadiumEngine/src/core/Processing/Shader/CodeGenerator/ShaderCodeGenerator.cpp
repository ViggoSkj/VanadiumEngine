#include "pch.h"
#include "ShaderCodeGenerator.h"
#include "core/IO/IFileLoader.h"
#include "core/AssetManager/AssetManager.h"
#include "core/AssetManager/AssetTypes/Shader/ShaderAsset.h"

namespace Vanadium::Detail::ShaderCodeGenerator
{
	void ExecuteIncludes(ShaderProcessingObject& processingObject, IShaderCodeLoader* codeLoader)
	{
		i32 tokenCursor = -1;
		while ((tokenCursor = processingObject.Tokenized.FindHint("#include")) != -1)
		{
			// load included code
			std::string_view pathArg = processingObject.Tokenized.Tokens()[tokenCursor + 1].Text;
			std::filesystem::path path(pathArg);
			ShaderProcessingObject* included = codeLoader->LoadShaderCode(path);

			// insert into current source
			processingObject.Replace(tokenCursor, tokenCursor + 2, *included);
		}

		processingObject.Tokenized = Tokenizer::Tokenize(processingObject.Source);
	}
}