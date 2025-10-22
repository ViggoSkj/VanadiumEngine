#include "pch.h"
#include "EntityComponentSystem.h"
#include "core/Debug/Log.h"

EntityComponentSystem::~EntityComponentSystem()
{
	m_entities.clear();
}

EntityRef EntityComponentSystem::CreateEntity(SceneRef sceneRef)
{
	m_entities.emplace_back(&m_storeManager, s_nextEntityId++, sceneRef, this);
	m_entityIdIndexMap.InsertLookup(m_entities.back().GetId(), m_entities.size() - 1);
	return EntityRef(m_entities.back().GetId(), this);
}

std::optional<Entity*> EntityComponentSystem::FindEntity(u32 id)
{
	size_t entityIndex = m_entityIdIndexMap.GetIndex(id);

	if (entityIndex == -1)
		return std::nullopt;

	return std::optional<Entity*>(&m_entities[entityIndex]);
}

void EntityComponentSystem::DeleteEntity(u32 id)
{
	unsigned int index = m_entityIdIndexMap.MarkRemoved(id);
	m_entities.remove(index);
	LogDebug("Entity deleted");
}

void EntityComponentSystem::DeleteEntity(EntityRef ref)
{
	DeleteEntity(ref.GetId());
}

void EntityComponentSystem::SignalOwnerDeleted(unsigned int owner)
{
	throw "IMPLEMENT";
}

void EntityComponentSystem::Flush()
{
	m_entityIdIndexMap.Flush();
	m_storeManager.Flush();
}