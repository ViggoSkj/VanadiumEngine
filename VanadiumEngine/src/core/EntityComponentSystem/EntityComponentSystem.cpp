#include "EntityComponentSystem.h"

Entity& EntityComponentSystem::CreateEntity(unsigned int owner)
{
	m_entities.emplace_back(&m_storeManager, s_nextEntityId++, owner);
	m_entityIdIndexMap.InsertLookup(m_entities.back().GetId(), m_entities.size() - 1);
	return m_entities.back();
}

Entity& EntityComponentSystem::FindEntity(unsigned int id)
{
	unsigned int entityIndex = m_entityIdIndexMap.GetIndex(id);
	return m_entities[entityIndex];
}

void EntityComponentSystem::SignalOwnerDeleted(unsigned int owner)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities[i].GetOwner() == owner)
		{
			m_entityIdIndexMap.MarkRemoved(m_entities[i].GetId());
			m_entities[i];
			m_entities.remove(i);
		}
	}
}