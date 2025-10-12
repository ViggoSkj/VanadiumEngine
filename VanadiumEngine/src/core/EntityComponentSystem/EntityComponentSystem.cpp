#include "pch.h"
#include "EntityComponentSystem.h"

EntityComponentSystem::~EntityComponentSystem()
{
	m_entities.clear();
}

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

void EntityComponentSystem::DeleteEntity(unsigned int id)
{
	unsigned int index = m_entityIdIndexMap.MarkRemoved(id);
	m_entities.remove(index);
}

void EntityComponentSystem::SignalOwnerDeleted(unsigned int owner)
{
	while (m_entities.size() > 0)
	{
		if (m_entities.back().GetOwner() == owner)
		{
			DeleteEntity(m_entities.back().GetId());
		}
	}
}