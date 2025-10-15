#pragma once
#include "pch.h"
#include <stdint.h>

class EntityComponentSystem;

class Component
{
public:
	Component() = default;
	Component(Component&&) noexcept = default;
	Component& operator=(Component&&) noexcept = default;
	Component(const Component&) = delete;
	Component(unsigned int owner);

	unsigned int GetId() const { return m_id; };
	unsigned int GetOwnerId() const { return m_owner; };

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& GetComponent()
	{
		return ECS().FindEntity(GetOwnerId()).GetComponent<TComponent>();
	}
protected:
	EntityComponentSystem& ECS();

private:
	static unsigned int m_nextId;
	unsigned int m_id;
	unsigned int m_owner;
};

inline unsigned int Component::m_nextId = 0;


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