#include "pch.h"
#include "Component.h"
#include <iostream>
#include "Application.h"
#include "core/EntityComponentSystem/EntityComponentSystem.h"

namespace Vanadium
{
	using Vanadium::Application;

	Component::Component(EntityRef entityRef)
		: m_id(Component::m_nextId++), m_entityRef(entityRef)
	{

	}

	u32 Component::GetOwnerId() const
	{
		return m_entityRef.GetId();
	}

	Entity& Component::GetEntity()
	{
		return m_entityRef.Get();
	}

	SceneRef Component::GetSceneRef()
	{
		return GetEntity().GetSceneRef();
	}

	EntityComponentSystem& Component::ECS()
	{
		return *Application::Get().GetECS();
	}
}