#pragma once
#include "pch.h"
#include <optional>

#include "Util.h"
#include "Component.h"
#include "core/Util/IdIndexMap.h"
#include "core/Util/UnorderdVector.h"
#include "IComponentStore.h"

template <typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
class ComponentStore : public IComponentStore
{
public:
	ComponentStore()
		: IComponentStore(GetComponentTypeId<TComponent>()) {
	}
	ComponentStore(const ComponentStore<TComponent>&) = delete;

	unsigned int CreateInstance(unsigned int owner)
	{
		m_components.emplace_back(owner);
		m_idIndexMap.InsertLookup(m_components.back().GetId(), m_components.size() - 1);
		return m_components.back().GetId();
	}

	TComponent& GetComponent(unsigned int id)
	{
		return m_components[m_idIndexMap.GetIndex(id)];
	}

	void DeleteInstance(unsigned int ref) override
	{
		unsigned int componentIndex = m_idIndexMap.MarkRemoved(ref);
		unsigned int movedComponentId = m_components.back().GetId();

		if (m_components[componentIndex].GetId() != movedComponentId)
			m_idIndexMap.UpdateIndex(movedComponentId, componentIndex);

		m_components.remove(componentIndex);

		if (m_idIndexMap.EmptySlotCount() > 100)
			m_idIndexMap.Flush();
	}

	void MarkOwnerRemoved(unsigned int ownerId)
	{
		// TODO: Implement
	}

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