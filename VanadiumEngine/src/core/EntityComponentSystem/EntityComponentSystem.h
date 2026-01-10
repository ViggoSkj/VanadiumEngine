#pragma once
#include "pch.h"
#include "Entity.h"
#include "Component.h"
#include "ComponentStore.h"
#include "core/Util/UnorderdVector.h"
#include "core/Util/IdIndexMap.h"
#include "core/Scene/SceneRef.h"
#include "ComponentStoreManger.h"
#include "EntityRef.h"

namespace Vanadium
{
	class Entity;

	class EntityComponentSystem
	{
	public:
		EntityComponentSystem() = default;
		EntityComponentSystem(const EntityComponentSystem&) = delete;

		~EntityComponentSystem();

		EntityRef CreateEntity(SceneRef sceneRef);
		Entity* FindEntity(u32 id);
		void DeleteEntity(u32 id);
		void DeleteEntity(EntityRef ref);

		void SignalOwnerDeleted(unsigned int owner);

		template<typename TComponent>

		ComponentStore<TComponent>* GetComponentStore()
		{
			return m_storeManager.GetComponentStore<TComponent>();
		}

		void Flush();

		void AwakeComponents() { m_storeManager.AwakeComponents(); }

	private:
		static unsigned int s_nextEntityId;

		UnorderedVector<Entity> m_entities;
		IdIndexMap m_entityIdIndexMap;

		ComponentStoreManager m_storeManager;
	};

	inline unsigned int EntityComponentSystem::s_nextEntityId = 1;
}