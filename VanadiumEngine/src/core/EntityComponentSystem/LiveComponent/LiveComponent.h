#pragma once
#include "pch.h"
#include "core/EntityComponentSystem/EntityComponentSystem.h"

class LiveComponent : public Component
{
public:
	LiveComponent(LiveComponent&&) noexcept = default;
	LiveComponent& operator=(LiveComponent&&) noexcept = default;

	LiveComponent(const LiveComponent&) = delete;
	LiveComponent(unsigned int owner)
		: Component(owner) {
	};

	virtual void OnUpdate(double dt) {};
	virtual void OnRender(double dt) {};

protected:
	EntityComponentSystem& ECS();
	
	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& GetComponent()
	{
		return ECS().FindEntity(GetOwnerId()).GetComponent<TComponent>();
	}
};