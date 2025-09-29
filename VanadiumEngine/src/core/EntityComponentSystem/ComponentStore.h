#pragma once
#include <optional>
#include <vector>
#include "Util.h"
#include "Component.h"
#include "core/Util/IdIndexMap.h"
#include "core/Util/UnorderdVector.h"

typedef unsigned int ComponentRef;

template <typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
class ComponentStore
{
public:

	ComponentRef CreateInstance(unsigned int owner)
	{
		m_components.emplace_back(owner);
		m_idIndexMap.InsertLookup(m_components.back().GetId(), m_components.size() - 1);
		return ComponentRef(m_components.back().GetId());
	}

	TComponent& GetComponent(ComponentRef ref)
	{
		return m_components[m_idIndexMap.GetIndex(ref)];
	}

	void DeleteInstance(ComponentRef ref);

	UnorderedVector<TComponent>& GetComponents() { return m_components; };

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
	IdIndexMap m_idIndexMap;
};

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline void ComponentStore<TComponent>::DeleteInstance(ComponentRef ref)
{
	unsigned int componentIndex = m_idIndexMap.MarkRemoved(ref);
	m_idIndexMap.UpdateComponentIndex(m_components.back().GetId(), componentIndex);
	m_components.remove(componentIndex);

	if (m_idIndexMap.EmptySlots.size() > 100)
		m_idIndexMap.Flush();
}