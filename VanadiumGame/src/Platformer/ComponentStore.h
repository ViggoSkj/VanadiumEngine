#pragma once
#include "Utility.h"
#include "Component.h"

template <typename T>
struct ComponentRef
{
	unsigned int Id;
};


template <typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
class ComponentStore
{
	ComponentRef<TComponent> CreateInstance()
	{
		m_components.PushBack();
		m_lookups.PushBack(ComponentLookup(m_components.Last(), m_components.Size() - 1));
		return m_components.PushBack();
	}

	unsigned int GetIndex(const ComponentRef<TComponent>& ref);
	void DeleteInstance(ComponentRef<TComponent> ref);

	void SortLookups();

private:
	struct ComponentLookup
	{
		ComponentLookup(unsigned int id, unsigned int index)
			: Id(id), Index(index) {};

		unsigned int Id;
		unsigned int Index;
	};

	UnorderedVector<TComponent> m_components;
	UnorderedVector<ComponentLookup> m_lookups;
};

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline unsigned int ComponentStore<TComponent>::GetIndex(const ComponentRef<TComponent>& ref)
{
	// binary search

	int left = 0;
	int right = m_lookups.Size() - 1;
	ComponentLookup lookup;

	while ((lookup = m_lookups[(left + right) / 2]).id != ref.Id)
	{
		if (lookup.id > ref.id)
			left = (left + right) / 2;
		else
			right = (left + right) / 2;
	}

	return lookup.Index;
}

template<typename TComponent>
inline void ComponentStore<TComponent>::DeleteInstance(ComponentRef<TComponent> ref)
{
	unsigned index = GetIndex(ref);
	m_components.Remove(index);
	m_lookups.Remove(index);
	SortLookups();
}

template<typename TComponent>
inline void ComponentStore<TComponent>::SortLookups()
{
}
