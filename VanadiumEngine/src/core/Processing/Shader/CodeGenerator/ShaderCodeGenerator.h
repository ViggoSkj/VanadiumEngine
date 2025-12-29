#pragma once
#include "pch.h"
#include "core/Processing/Shader/IShaderCodeLoader.h"
#include "core/Processing/Shader/ShaderProcessingObject.h"


namespace Vanadium::Detail::ShaderCodeGenerator
{
	void ExecuteIncludes(ShaderProcessingObject& processingObject, IShaderCodeLoader* codeLoader);
}