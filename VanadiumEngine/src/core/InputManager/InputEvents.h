#pragma once
#include "core/Events.h"

namespace Vanadium
{
	class MouseButtonEvent : public Event
	{
	public:

		Vector2I Position;
		i32 MouseButton;
	private:
	};

	class MouseButtonDownEvent : public MouseButtonEvent
	{
	public:

		EVENT_CLASS_TYPE(MouseButtonDown);

	private:
	};
}