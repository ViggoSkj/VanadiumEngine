#pragma once
#include "pch.h"
#include <filesystem>
#include "ShaderProcessingObject.h"

struct IShaderCodeLoader
{
	virtual ShaderProcessingObject* LoadShaderCode(std::filesystem::path path) { return (ShaderProcessingObject*) 1; };
};