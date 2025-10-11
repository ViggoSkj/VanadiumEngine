#pragma once
#include "core/Processing/Shader/IShaderCodeLoader.h"
#include "core/Processing/Shader/ShaderProcessingObject.h"


namespace ShaderCodeGenerator
{
	void ExecuteIncludes(ShaderProcessingObject& processingObject, IShaderCodeLoader* codeLoader);
}