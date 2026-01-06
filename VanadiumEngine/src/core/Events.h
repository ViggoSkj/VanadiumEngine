#pragma once
#include "core/CoreTypes.h"
#include <functional>

namespace Vanadium
{

	enum class EventType
	{
		None = 0,

		MouseButtonDown,
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\

	class Event
	{
	public:
		virtual ~Event() {};
		virtual EventType GetEventType() const = 0;

		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_event(event)
		{

		}

		template<typename T>
		bool Dispatch(std::function<bool(T&)> eventFn)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				m_event.Handled = eventFn(*(T*)&m_event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};
}