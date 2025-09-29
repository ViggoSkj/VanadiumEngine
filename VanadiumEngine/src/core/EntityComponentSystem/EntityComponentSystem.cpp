#include "EntityComponentSystem.h"

Entity& EntityComponentSystem::CreateEntity()
{
	m_entities.emplace_back(s_nextEntityId++);
	m_entityIdIndexMap.InsertLookup(m_entities.back().GetId(), m_entities.size() - 1);
	return m_entities.back();
}

Entity& EntityComponentSystem::FindEntity(unsigned int id)
{
	unsigned int entityIndex = m_entityIdIndexMap.GetIndex(id);
	return m_entities[entityIndex];
}
