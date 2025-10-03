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

	std::vector<ComponentRef> m_components;

	unsigned int GetId() const { return m_id; };
	unsigned int GetOwner() const { return m_owner; };
private:
	unsigned int m_id;
	unsigned int m_owner;

	ComponentStoreManager* m_storeManager;
};

inline unsigned int Entity::nextComponentId = 0;