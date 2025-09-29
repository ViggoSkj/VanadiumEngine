#pragma once
#include "Entity.h"
#include "Component.h"
#include "ComponentStore.h"
#include "core/Util/UnorderdVector.h"
#include "core/Util/IdIndexMap.h"

class EntityComponentSystem
{
public:
	EntityComponentSystem() = default;
	EntityComponentSystem(const EntityComponentSystem&) = delete;

	Entity& CreateEntity();
	Entity& FindEntity(unsigned int id);

private:
	static unsigned int s_nextEntityId;

	UnorderedVector<Entity> m_entities;
	IdIndexMap m_entityIdIndexMap;
};

inline unsigned int EntityComponentSystem::s_nextEntityId = 1;