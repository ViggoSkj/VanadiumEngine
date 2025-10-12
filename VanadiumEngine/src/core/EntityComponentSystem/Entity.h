#pragma once
#include "pch.h"
#include <memory>

#include "Component.h"
#include "ComponentStore.h"
#include "ComponentStoreManger.h"

class Entity
{
public:
	static unsigned int nextComponentId;

	Entity(ComponentStoreManager* storeManager, unsigned int id, unsigned int owner)
		: m_storeManager(storeManager), m_id(id), m_owner(owner) {
	};
	Entity(Entity&& other) noexcept
		: m_storeManager(other.m_storeManager), m_id(other.m_id), m_owner(other.m_owner), m_componentReferences(std::move(other.m_componentReferences)) {
	}
	Entity(const Entity&) = delete;
	~Entity()
	{
		while (m_componentReferences.size() > 0)
		{
			unsigned int typeId = m_componentReferences.back().GetComponentTypeId();
			m_componentReferences.pop_back();
			IComponentStore* store = m_storeManager->GetComponentStore(typeId).value_or(nullptr);
			store->DeleteInstance(typeId);
		}
	}

	Entity& operator=(Entity&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_owner = other.m_owner;
			m_storeManager = other.m_storeManager;
			m_componentReferences = std::move(other.m_componentReferences);
		}

		return *this;
	}

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& AddComponent()
	{
		m_componentReferences.emplace_back(m_storeManager->AddComponent<TComponent>(m_id));
		return m_storeManager->GetComponent<TComponent>(m_componentReferences.back().GetComponentId());
	}

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& GetComponent()
	{
		unsigned int componentTypeId = GetComponentTypeId<TComponent>();
		unsigned int componentId = -1;

		for (int i = 0; i < m_componentReferences.size(); i++)
		{
			if (m_componentReferences[i].GetComponentTypeId() == componentTypeId)
				componentId = m_componentReferences[i].GetComponentId();
		}
		if (componentId == -1)
			throw "not found";

		return m_storeManager->GetComponent<TComponent>(componentId);
	}


	unsigned int GetId() const { return m_id; };
	unsigned int GetOwner() const { return m_owner; };
private:
	void RemoveComponent(unsigned int index)
	{
		unsigned int typeId = m_componentReferences[index].GetComponentTypeId();
		m_componentReferences.remove(index);
		IComponentStore* store = m_storeManager->GetComponentStore(typeId).value();
		store->DeleteInstance(index);
	}

	unsigned int m_id;
	unsigned int m_owner;

	UnorderedVector<ComponentRef> m_componentReferences;
	ComponentStoreManager* m_storeManager;
};

inline unsigned int Entity::nextComponentId = 0;