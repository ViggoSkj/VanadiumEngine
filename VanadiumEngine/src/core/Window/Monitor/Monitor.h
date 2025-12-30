#pragma once
#include <span>
#include "core/Rendering/GLCommon.h"
#include "core/util/RectI.h"

namespace Vanadium::Monitor
{
	std::span<GLFWmonitor*> GetMonitors();
	RectI GetWorkingArea(GLFWmonitor* monitor);
}