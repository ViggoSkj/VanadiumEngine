#pragma once
#include "pch.h"
#include "ShaderProcessingObject.h"

namespace Vanadium::Detail
{
	struct IShaderCodeLoader
	{
		virtual ShaderProcessingObject* LoadShaderCode(std::filesystem::path path) { return (ShaderProcessingObject*)1; };
	};
}