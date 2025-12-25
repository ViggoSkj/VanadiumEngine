#pragma once
#include "pch.h"
#include <memory>
#include "Component.h"
#include "ComponentStore.h"
#include "ComponentStoreManger.h"
#include "core/Scene/SceneRef.h"

class EntityComponentSystem;

class Entity
{
public:
	static unsigned int nextComponentId;

	Entity(ComponentStoreManager* storeManager, unsigned int id, SceneRef sceneRef, EntityComponentSystem* ecs)
		: m_storeManager(storeManager), m_id(id), m_sceneRef(sceneRef), m_ecs(ecs) {
	};
	Entity(Entity&& other) noexcept
		: m_storeManager(other.m_storeManager), m_id(other.m_id), m_sceneRef(other.m_sceneRef), m_componentReferences(std::move(other.m_componentReferences)), m_ecs(other.m_ecs) {
	}
	Entity(const Entity&) = delete;
	~Entity()
	{
		while (m_componentReferences.size() > 0)
		{
			unsigned int typeId = m_componentReferences.back().GetComponentTypeId();
			IComponentStore* store = m_storeManager->GetComponentStore(typeId).value_or(nullptr);
			store->DeleteInstance(m_componentReferences.back().GetComponentId());
			m_componentReferences.pop_back();
		}
	}

	Entity& operator=(Entity&& other) noexcept
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_sceneRef = other.m_sceneRef;
			m_storeManager = other.m_storeManager;
			m_componentReferences = std::move(other.m_componentReferences);
		}

		return *this;
	}

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent* AddComponent()
	{
		m_componentReferences.emplace_back(m_storeManager->AddComponent<TComponent>(EntityRef(m_id, m_ecs)));
		return m_storeManager->GetComponent<TComponent>(m_componentReferences.back().GetComponentId()).value();
	}

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent* GetComponent()
	{
		u32 componentTypeId = GetComponentTypeId<TComponent>();
		u32 componentId = -1;

		for (int i = 0; i < m_componentReferences.size(); i++)
		{
			if (m_componentReferences[i].GetComponentTypeId() == componentTypeId)
				componentId = m_componentReferences[i].GetComponentId();
		}

		if (componentId == -1)
			return nullptr;

		return m_storeManager->GetComponent<TComponent>(componentId);
	}

	Scene& GetScene()
	{
		return m_sceneRef.Get();
	}
	u32 GetId() const { return m_id; };
	u32 GetOwner() const;
private:
	void RemoveComponent(unsigned int index)
	{
		unsigned int typeId = m_componentReferences[index].GetComponentTypeId();
		m_componentReferences.remove(index);
		IComponentStore* store = m_storeManager->GetComponentStore(typeId).value();
		store->DeleteInstance(index);
	}

	u32 m_id;

	SceneRef m_sceneRef;
	UnorderedVector<ComponentRef> m_componentReferences;
	ComponentStoreManager* m_storeManager;
	EntityComponentSystem* m_ecs;
};

inline unsigned int Entity::nextComponentId = 0;