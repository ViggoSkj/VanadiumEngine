#pragma once
#include <optional>
#include <vector>
#include "Utility.h"
#include "Component.h"


struct ComponentLookup
{
	ComponentLookup() = default;
	ComponentLookup(unsigned int id, unsigned int componentIndex)
		: Id(id), ComponentIndex(componentIndex) {
	};

	unsigned int Id = 0;
	unsigned int ComponentIndex = 0;
};

struct ComponentTracker
{
	void InsertLookup(unsigned int id, unsigned int componentIndex);
	unsigned int FindLookupIndex(unsigned int id);
	unsigned int MarkRemoved(unsigned int id);
	void Sort();
	void Flush();
	void UpdateComponentIndex(unsigned int id, unsigned int newComponentIndex);

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
		m_tracker.InsertLookup(m_components.Last().GetId(), m_components.Size() - 1);
		return ComponentRef<TComponent>(m_components.Last().GetId());
	}

	void DeleteInstance(ComponentRef<TComponent> ref);

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
	ComponentTracker m_tracker;
};

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline void ComponentStore<TComponent>::DeleteInstance(ComponentRef<TComponent> ref)
{
	unsigned int componentIndex = m_tracker.MarkRemoved(ref.Id);
	m_tracker.UpdateComponentIndex(m_components.Last().GetId(), componentIndex);
	m_components.Remove(componentIndex);

	if (m_tracker.EmptySlots.size() > 100)
		m_tracker.Flush();
}