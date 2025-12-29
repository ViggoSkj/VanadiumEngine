#pragma once
#include "pch.h"

namespace Vanadium
{
	struct IFileLoader
	{
		virtual std::string LoadFile(std::filesystem::path path) {};
	};
}