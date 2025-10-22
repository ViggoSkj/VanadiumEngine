#pragma once
#include "pch.h"
#include "core/EntityComponentSystem/EntityRef.h"
#include <stdint.h>

class Entity;
class EntityComponentSystem;

class Component
{
public:
	Component() = default;
	Component(Component&&) noexcept = default;
	Component& operator=(Component&&) noexcept = default;
	Component(const Component&) = delete;
	Component(EntityRef entityRef);

	unsigned int GetId() const { return m_id; };
	u32 GetOwnerId() const;
	Entity& GetEntity();

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	std::optional<TComponent*> GetComponent()
	{
		return ECS().FindEntity(GetOwnerId()).value()->GetComponent<TComponent>();
	}
protected:
	EntityComponentSystem& ECS();

private:
	static u32 m_nextId;
	u32 m_id;
	EntityRef m_entityRef;
};

inline u32 Component::m_nextId = 0;


template<typename TComponent>
struct ComponentTypeId
{
	static unsigned int Id;
};

template<typename TComponent>
inline uint32_t ComponentTypeId<TComponent>::Id;

template<typename TComponent>
unsigned int GetComponentTypeId()
{
	return reinterpret_cast<unsigned int>(&ComponentTypeId<TComponent>::Id);
}