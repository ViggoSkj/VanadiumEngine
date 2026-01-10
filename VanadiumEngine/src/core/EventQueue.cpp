#include "pch.h"
#include "EventQueue.h"
#include <memory>

namespace Vanadium
{
	EventQueue::EventQueue()
	{
		Resize(1000);
	}

	Event* EventQueue::PopEvent()
	{
		assert(m_eventCount > 0);

		EventHeader* header = reinterpret_cast<EventHeader*>(m_readPointer);
		
		m_readPointer += sizeof(EventHeader);

		Event* e = reinterpret_cast<Event*>(m_readPointer);

		m_readPointer += header->size;

		m_eventCount--;

		return e;
	}

	void EventQueue::Flush()
	{
		m_eventCount = 0;
		m_readPointer = m_data;
		m_insertPointer = m_data;
	}

	bool EventQueue::Empty() const
	{
		return m_eventCount < 1;
	}

	void EventQueue::Resize(size_t size)
	{
		std::byte* newData = (std::byte*)malloc(size);

		assert(newData != nullptr); // TODO: how do you handle when you cant alloc?

		if (m_data != nullptr)
		{
			m_readPointer = newData + (m_readPointer - m_data);
			m_insertPointer = newData + (m_insertPointer - m_data);
			memcpy(newData, m_data, size);
			free(m_data);
		}
		else
		{
			m_insertPointer = newData;
			m_readPointer = newData;
		}

		m_data = newData;
	}
}