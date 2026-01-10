#pragma once
#include "core/Events.h"

namespace Vanadium
{
	struct EventHeader
	{
		template<typename T>
		static EventHeader Create()
		{
			return {
				T::GetStaticType(),
				sizeof(T)
			};
		}

		EventType type;
		i32 size;
	};

	class EventQueue
	{
	public:
		EventQueue();

		template<typename T>
		void Push(T& event);
		Event* PopEvent();
		void Flush();

		bool Empty() const;

		std::byte* End() const { return m_data + m_size; }

	private:
		void Resize(size_t size);

		template<typename T>
		size_t RequiredSize() const;

		i32 m_eventCount = 0;

		size_t m_size = 0;
		std::byte* m_insertPointer = nullptr;
		std::byte* m_readPointer = nullptr;
		std::byte* m_data = nullptr;
	};

	template<typename T>
	inline void EventQueue::Push(T& event)
	{
		size_t size = RequiredSize<T>();
		if (m_insertPointer + size >= End())
			Resize(size * 1.5);

		EventHeader h = EventHeader::Create<T>();
		memcpy(m_insertPointer, &h, sizeof(EventHeader));
		m_insertPointer += sizeof(EventHeader);
		memcpy(m_insertPointer, &event, sizeof(T));
		m_insertPointer += sizeof(T);

		m_eventCount++;
	}

	template<typename T>
	inline size_t EventQueue::RequiredSize() const
	{
		return sizeof(T) + sizeof(EventHeader);
	}
}