#pragma once
#include <iostream>
#include "core/ApplicationLayer.h"
#include "core/Application.h"
#include "LiveComponent.h"

template <typename TComponent>
	requires std::is_base_of_v<LiveComponent, TComponent>
class LiveComponentLayer : public ApplicationLayer
{
public:
	void OnUpdate(double dt) override;
};

template <typename TComponent>
	requires std::is_base_of_v<LiveComponent, TComponent>
void LiveComponentLayer<TComponent>::OnUpdate(double dt)
{
	EntityComponentSystem& ECS = Application::Get().GetECS();
	ComponentStore<TComponent>& store = ECS.GetComponentStore<TComponent>();
	UnorderedVector<TComponent>& components = store.GetComponents();

	for (int i = 0; i < components.size(); i++)
	{
		components[i].OnUpdate(dt);
	}
}