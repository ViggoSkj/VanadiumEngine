#include "pch.h"
#include "ShaderCodeGenerator.h"
#include "core/IO/IFileLoader.h"
#include "core/AssetManager/AssetManager.h"
#include "core/AssetManager/AssetTypes/Shader/ShaderAsset.h"

namespace Vanadium::Detail::ShaderCodeGenerator
{
	// TODO: make able to import multiple things
	void ExecuteIncludes(ShaderProcessingObject& processingObject, IShaderCodeLoader* codeLoader)
	{
		i32 tokenCursor = -1;
		i32 sourceOffset = 0;
		while ((tokenCursor = processingObject.Tokenized.FindHint("#include", tokenCursor + 1)) != -1)
		{

			// load included code
			std::string_view pathArg = processingObject.Tokenized.Tokens()[tokenCursor + 1].Text;
			std::filesystem::path path(pathArg);
			ShaderProcessingObject* included = codeLoader->LoadShaderCode(path);

			// insert into current source
			processingObject.Source.replace(
				processingObject.Tokenized.Tokens()[tokenCursor].SourceIndex,
				processingObject.Tokenized.Tokens()[tokenCursor + 2].SourceIndex - processingObject.Tokenized.Tokens()[tokenCursor].SourceIndex - 1,
				included->Source
			);
			sourceOffset -= included->Source.size();
		}

		processingObject.Tokenized = Tokenizer::Tokenize(processingObject.Source);
	}
}