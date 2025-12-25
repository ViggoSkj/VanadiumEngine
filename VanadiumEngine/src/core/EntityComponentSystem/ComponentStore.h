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

	u32 CreateInstance(EntityRef ref)
	{
		m_components.emplace_back(ref);
		m_idIndexMap.InsertLookup(m_components.back().GetId(), m_components.size() - 1);
		return m_components.back().GetId();
	}

	TComponent* GetComponent(unsigned int id)
	{
		size_t index = m_idIndexMap.GetIndex(id);
		if (index == -1)
			return nullptr;
		return &m_components[index];
	}

	void DeleteInstance(u32 ref) override
	{
		unsigned int componentIndex = m_idIndexMap.MarkRemoved(ref);
		unsigned int movedComponentId = m_components.back().GetId();

		if (m_components[componentIndex].GetId() != movedComponentId)
			m_idIndexMap.UpdateIndex(movedComponentId, componentIndex);

		m_components.remove(componentIndex);
	}

	void MarkOwnerRemoved(unsigned int ownerId)
	{
		// TODO: Implement
	}

	void Flush() override
	{
		m_idIndexMap.Flush();
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