#pragma once
#include "pch.h"
class EntityComponentSystem;
class Entity;

class EntityRef
{
public:
	EntityRef() = default;
	EntityRef(u32 entityId, EntityComponentSystem* system)
		: m_entityId(entityId), m_system(system) {
	}

	std::optional<Entity*> GetEntity();
	Entity& Get();

	u32 GetId() const { return m_entityId; }

private:
	u32 m_entityId;
	EntityComponentSystem* m_system;
};