#include "pch.h"
#include "EntityRef.h"
#include "EntityComponentSystem.h"

std::optional<Entity*> EntityRef::GetEntity()
{
	return m_system->FindEntity(m_entityId);
}

Entity& EntityRef::Get()
{
	return *GetEntity().value();
}