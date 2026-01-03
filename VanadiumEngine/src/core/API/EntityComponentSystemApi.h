#pragma once
#include "core/Application.h"
#include "core/EntityComponentSystem/EntityComponentSystem.h"

namespace Vanadium::ECS
{
	template <typename TComponent>
	ComponentHandle<TComponent> CreateHandle(const TComponent& component)
	{
		auto store = Application::Get().GetECS()->GetComponentStore<TComponent>();
		return ComponentHandle(store, component.GetId());
	}
}