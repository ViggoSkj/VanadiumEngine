#pragma once
#include <memory>
#include <vector>
#include "Component.h"
#include "ComponentStore.h"
#include "ComponentStoreManger.h"

struct ComponentAccess
{
	ComponentAccess() = default;
	ComponentAccess(unsigned int ComponentTypeId, ComponentRef ref)
		: ComponentTypeId(ComponentTypeId), Ref(ref) {
	};

	unsigned int ComponentTypeId;
	ComponentRef Ref;
};

class Entity
{
public:
	static unsigned int nextComponentId;

	Entity(ComponentStoreManager* storeManager, unsigned int id, unsigned int owner)
		: m_storeManager(storeManager), m_id(id), m_owner(owner) {
	};
	Entity(Entity&& other) noexcept
		: m_storeManager(other.m_storeManager), m_id(other.m_id), m_owner(other.m_owner), m_components(std::move(other.m_components)) {
	}
	Entity(const Entity&) = delete;
	~Entity()
	{
		while (m_components.size() > 0)
		{
			unsigned int typeId = m_components.back().GetComponentTypeId();
			m_components.pop_back();
			IComponentStore& store = m_storeManager->GetComponentStore(typeId);
			store.DeleteInstance(typeId);
		}
	}

	Entity& operator=(Entity&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_owner = other.m_owner;
			m_storeManager = other.m_storeManager;
			m_components = std::move(other.m_components);
		}

		return *this;
	}

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& AddComponent()
	{
		m_components.emplace_back(m_storeManager->AddComponent<TComponent>(m_id));
		return m_storeManager->GetComponent<TComponent>(m_components.back().GetComponentId());
	}

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& GetComponent()
	{
		unsigned int componentTypeId = GetComponentTypeId<TComponent>();
		unsigned int componentId = -1;

		for (int i = 0; i < m_components.size(); i++)
		{
			if (m_components[i].GetComponentTypeId() == componentTypeId)
				componentId = m_components[i].GetComponentId();
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
		unsigned int typeId = m_components[index].GetComponentTypeId();
		m_components.remove(index);
		IComponentStore& store = m_storeManager->GetComponentStore(typeId);
		store.DeleteInstance(index);
	}

	unsigned int m_id;
	unsigned int m_owner;

	UnorderedVector<ComponentRef> m_components;
	ComponentStoreManager* m_storeManager;
};

inline unsigned int Entity::nextComponentId = 0;