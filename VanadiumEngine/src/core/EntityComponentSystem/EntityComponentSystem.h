#pragma once
#include "Entity.h"
#include "Component.h"
#include "ComponentStore.h"
#include "core/Util/UnorderdVector.h"
#include "core/Util/IdIndexMap.h"
#include "ComponentStoreManger.h"


class EntityComponentSystem
{
public:
	EntityComponentSystem() = default;
	EntityComponentSystem(const EntityComponentSystem&) = delete;

	~EntityComponentSystem();

	Entity& CreateEntity(unsigned int owner);
	Entity& FindEntity(unsigned int id);
	void DeleteEntity(unsigned int id);

	void SignalOwnerDeleted(unsigned int owner);

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	std::optional<ComponentStore<TComponent>*> GetComponentStore()
	{
		return m_storeManager.GetComponentStore<TComponent>();
	}

private:
	static unsigned int s_nextEntityId;

	UnorderedVector<Entity> m_entities;
	IdIndexMap m_entityIdIndexMap;

	ComponentStoreManager m_storeManager;
};

inline unsigned int EntityComponentSystem::s_nextEntityId = 1;