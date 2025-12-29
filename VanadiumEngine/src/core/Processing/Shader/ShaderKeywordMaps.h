#pragma once
#include "pch.h"
#include "ShaderKeyword.h"

namespace Vanadium::Detail
{
	inline const std::unordered_map<ShaderKeyword, std::string> ShaderKeywordToString = {
	{ Layout, "layout" },
	{ In, "in" },
	{ Uniform, "uniform" },
	{ Location, "location" },
	{ Const, "const" },
	};

	inline const std::unordered_map<std::string, ShaderKeyword> StringToShaderKeyword = {
		{ "layout", Layout },
		{ "in", In },
		{ "uniform", Uniform },
		{ "const", Const },
	};
}