#pragma once
#include "core/ErrorValue/ErrorValue.h"

namespace Vanadium
{
	void LogError(ErrorValue error);
	void LogDebug(std::string message);
	void LogInfo(std::string message);
}