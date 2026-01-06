#pragma once
#include <variant>
#include <functional>
#include "core/CoreTypes.h"
#include "core/Events.h"

namespace Vanadium
{
	struct WindowMonitorPosition
	{
		i32 monitorIndex;
	};

	enum class WindowPlacementType
	{
		None,
		Absolute,
		Monitor,
	};

	struct WindowOptions
	{
		WindowOptions(i32 width, i32 height, i32 x, i32 y)
			: placementType(WindowPlacementType::Absolute)
			, absolute({ x, y })
			, width(width), height(height)
		{

		}

		WindowOptions(i32 width, i32 height, i32 monitor)
			: placementType(WindowPlacementType::Monitor)
			, monitor(WindowMonitorPosition{ monitor })
			, width(width), height(height)
		{

		}

		WindowPlacementType placementType;

		i32 width;
		i32 height;

		std::function<void(Event&)> eventCallback = [](Event& e) {};

		union
		{
			Vector2I absolute;
			WindowMonitorPosition monitor;
		};
	};
}