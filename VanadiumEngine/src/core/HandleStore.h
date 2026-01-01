#pragma once
#include "pch.h"
#include "core/CoreTypes.h"

namespace Vanadium
{
	template <typename T>
	struct HandleStoreEntry
	{
		std::optional<T> entry;
		u32 generation;
	};

	template <typename T>
	class Handle
	{
		template <typename T>
		friend class HandleStore;
	public:
		Handle(u32 index, u32 generation)
			: m_index(index), m_generation(generation)
		{

		}

	private:

		u32 m_generation = 0;
		u32 m_index;
	};

	template <typename T>
	class HandleStore
	{
	public:

		class Iterator
		{
		public:
			Iterator(HandleStoreEntry<T>* ptr, HandleStore<T>* store)
				: m_ptr(ptr), m_store(store)
			{

			}

			T& operator*() const { return m_ptr->entry.value(); }

			Iterator& operator++()
			{
				m_ptr++;
				while (m_ptr != m_store->end().m_ptr && !m_ptr->entry.has_value())
					m_ptr++;
				return *this;
			}

			bool operator!=(const Iterator& other) const
			{
				return m_ptr != other.m_ptr || m_store != other.m_store;
			}

		private:
			HandleStoreEntry<T>* m_ptr;
			HandleStore<T>* m_store;
		};

		Iterator begin()
		{
			i32 firstValid = FirstValid();
			if (firstValid == -1)
				return end();
			return Iterator(&m_entries.at(firstValid), this);
		}

		Iterator end() { return Iterator(m_entries.data() + m_entries.size(), this); }

		template <typename... Args>
		Handle<T> Create(Args&&... args)
		{
			u32 index = 0;
			if (m_freeSlots.size() > 0)
			{
				index = m_freeSlots.back();
				m_entries[index].entry.emplace(std::forward<Args>(args)...);
				m_freeSlots.pop_back();
			}
			else
			{
				m_entries.push_back({
					std::nullopt,
					0,
					});
				index = m_entries.size() - 1;
				m_entries[index].entry.emplace(std::forward<Args>(args)...);
			}

			m_entries[index].generation++;

			return { index, m_entries[index].generation };
		}

		T* Get(Handle<T> handle)
		{
			if (!IsValid(handle))
				return nullptr;

			return &m_entries[handle.m_index].entry.value();
		}

		bool IsValid(Handle<T> handle)
		{
			if (handle.m_index >= m_entries.size())
				return false;

			if (m_entries[handle.m_index].generation != handle.m_generation)
				return false;

			if (!m_entries[handle.m_index].entry.has_value())
				return false;

			return true;
		}
	private:
		i32 FirstValid()
		{
			for (i32 i = 0; i < m_entries.size(); i++)
			{
				if (m_entries[i].entry.has_value())
					return i;
			}
			return -1;
		}

		std::vector<HandleStoreEntry<T>> m_entries;
		std::vector<i32> m_freeSlots;
	};
}