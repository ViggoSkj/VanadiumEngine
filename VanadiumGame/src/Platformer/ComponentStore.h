#pragma once
#include <optional>
#include <vector>
#include "Utility.h"
#include "Component.h"


struct ComponentLookup
{
	ComponentLookup() = default;
	ComponentLookup(unsigned int id, unsigned int index)
		: Id(id), Index(index) {
	};

	unsigned int Id = 0;
	unsigned int Index = 0;
};

struct ComponentTracker
{
	unsigned int FindLookupIndex();
	void Flush();

	std::vector<ComponentLookup> Lookups;
	std::vector<unsigned int> EmptySlots;
};










template <typename T>
struct ComponentRef
{
	unsigned int Id;
};


template <typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
class ComponentStore
{
public:
	ComponentRef<TComponent> CreateInstance()
	{
		m_components.PushBack(TComponent());
		m_lookups.PushBack(ComponentLookup(m_components.Last().GetId(), m_components.Size() - 1));
		return ComponentRef<TComponent>(m_components.Last().GetId());
	}

	unsigned int GetIndex(const ComponentRef<TComponent>& ref);
	void DeleteInstance(ComponentRef<TComponent> ref);

	void SortLookups();

private:
	struct ComponentLookup
	{
		ComponentLookup() = default;
		ComponentLookup(unsigned int id, unsigned int index)
			: Id(id), Index(index) {
		};

		unsigned int Id = 0;
		unsigned int Index = 0;
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
	ComponentLookup lookup = m_lookups.Get((left + right) / 2);

	int maxIterations = log2(m_lookups.Size()) + 2;

	int i = 0;
	while (lookup.Id != ref.Id && i < maxIterations)
	{
		if (lookup.Id <= ref.Id)
			left = ceil((left + right) / 2.0f);
		else
			right = floor((left + right) / 2.0f);

		lookup = m_lookups.Get((left + right) / 2);

		i++;
	}

	if (i == maxIterations)
		return -1;

	return (left + right) / 2;
}

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline void ComponentStore<TComponent>::DeleteInstance(ComponentRef<TComponent> ref)
{
	unsigned int removedLookupIndex = GetIndex(ref);
	if (removedLookupIndex == -1)
		throw "no such instance";

	unsigned int removedComponentIndex = m_lookups.Get(removedLookupIndex).Index;

	unsigned int movedComponentLookupIndex = GetIndex(ComponentRef<TComponent>(m_components.Last().GetId()));

	if (movedComponentLookupIndex == -1)
		throw "no such instance 2";

	m_lookups.Set(movedComponentLookupIndex, ComponentLookup(m_components.Last().GetId(), removedComponentIndex));
	m_lookups.Remove(removedLookupIndex);
	m_components.Remove(removedComponentIndex);

	SortLookups();
}

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline void ComponentStore<TComponent>::SortLookups()
{
	int layerSize = 1;

	int totalValues = m_lookups.Size();

	while (layerSize < totalValues)
	{
		int pointer = 0;
		while (pointer + layerSize < totalValues)
		{
			int leftPointer = pointer;
			int rightPointer = pointer + layerSize;

			int valuesLeft = std::min(layerSize * 2, totalValues - pointer);
			int lastIndex = pointer + valuesLeft - 1;

			while (rightPointer <= lastIndex && leftPointer <= lastIndex)
			{
				if (m_lookups.Get(leftPointer).Id >= m_lookups.Get(rightPointer).Id)
				{
					m_lookups.Swap(leftPointer, rightPointer);
					rightPointer++;
				}

				leftPointer++;
			}
			pointer += layerSize * 2;
		}
		layerSize *= 2;
	}
}