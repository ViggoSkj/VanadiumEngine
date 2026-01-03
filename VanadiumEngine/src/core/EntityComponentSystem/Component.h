#pragma once
#include "pch.h"
#include <concepts>
#include "core/Scene/SceneRef.h"
#include "core/EntityComponentSystem/EntityRef.h"
#include "core/EntityComponentSystem/ComponentHandle.h"

namespace Vanadium
{
	class Entity;
	class EntityComponentSystem;

	class ComponentData
	{
	public:
		ComponentData() = delete;
		ComponentData(u32 id, EntityRef ref)
			: m_id(id)
			, m_entityRef(ref)
		{
		}

		unsigned int GetId() const { return m_id; };
		EntityRef GetEntityRef() const { return m_entityRef; }
		u32 GetOwnerId() const { return m_entityRef.GetId(); };
		Entity& GetEntity() { return m_entityRef.Get(); };

	protected:
		u32 m_id;
		EntityRef m_entityRef;
	};

	class Component
	{
	public:
		Component() = delete;
		Component(ComponentData data)
			: m_data(data)
		{

		}
		u32 GetId() const { return m_data.GetId(); }
		Entity& GetEntity() { return m_data.GetEntity(); }
		EntityRef GetEntityRef() const { return m_data.GetEntityRef(); }

	private:
		ComponentData m_data;
	};
}