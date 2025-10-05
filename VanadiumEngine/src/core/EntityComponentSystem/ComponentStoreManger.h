#pragma once
#include "IComponentStore.h"
#include "ComponentStore.h"
#include "Component.h"

class ComponentRef
{
public:
	ComponentRef(unsigned int componentId, unsigned int componentTypeId)
		: m_componentId(componentId), m_componentTypeId(componentTypeId)
	{

	};

	unsigned int GetComponentId() const { return m_componentId; };
	unsigned int GetComponentTypeId() const { return m_componentTypeId; };

private:
	unsigned int m_componentId;
	unsigned int m_componentTypeId;
};

class ComponentStoreManager
{
public:

	// TODO: test if it is faster to split creating and getting into two functions and having to manualy initialise component stores.
	template <typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	std::optional<ComponentStore<TComponent>*> GetComponentStore()
	{
		for (int i = 0; i < m_stores.size(); i++)
		{
			if (m_stores[i]->GetId() == GetComponentTypeId<TComponent>())
				return static_cast<ComponentStore<TComponent>*>(m_stores[i].get());
		}
		// create component store
		std::unique_ptr<ComponentStore<TComponent>> store();
		m_stores.push_back(std::make_unique<ComponentStore<TComponent>>());
		return static_cast<ComponentStore<TComponent>*>(m_stores.back().get());
	}

	std::optional<IComponentStore*> GetComponentStore(unsigned int id)
	{
		for (int i = 0; i < m_stores.size(); i++)
		{
			if (m_stores[i]->GetId() == id)
				return m_stores[i].get();
		}

		return std::nullopt;
	}

	template <typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	ComponentRef AddComponent(unsigned int owner)
	{
		ComponentStore<TComponent>* componentStore = GetComponentStore<TComponent>().value();
		unsigned int componentId = componentStore->CreateInstance(owner);
		return ComponentRef(componentId, componentStore->GetId());
	}

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& GetComponent(unsigned int componentId)
	{
		ComponentStore<TComponent>* store = GetComponentStore<TComponent>().value();
		return store->GetComponent(componentId);
	}


private:
	std::vector<std::unique_ptr<IComponentStore>> m_stores;
};