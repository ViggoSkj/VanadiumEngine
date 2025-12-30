#include "pch.h"
#include "Monitor.h"

namespace Vanadium::Monitor
{
	std::span<GLFWmonitor*> GetMonitors()
	{
		i32 count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		std::span<GLFWmonitor*> view(monitors, count);
		return view;
	}

	RectI GetWorkingArea(GLFWmonitor* monitor)
	{
		i32 xPos, yPos, width, height;
		glfwGetMonitorWorkarea(monitor, &xPos, &yPos, &width, &height);
		return RectI({ xPos, yPos }, { xPos + width, yPos + height });
	}
}