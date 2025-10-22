#pragma once
#include "pch.h"
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
	void OnRender(double dt) override;
};

template <typename TComponent>
	requires std::is_base_of_v<LiveComponent, TComponent>
void LiveComponentLayer<TComponent>::OnUpdate(double dt)
{
	EntityComponentSystem* ECS = Application::Get().GetECS();
	ComponentStore<TComponent>* store = ECS->GetComponentStore<TComponent>().value();
	UnorderedVector<TComponent>& components = store->GetComponents();

	for (int i = 0; i < components.size(); i++)
	{
		components[i].OnUpdate(dt);
	}
}

template <typename TComponent>
	requires std::is_base_of_v<LiveComponent, TComponent>
void LiveComponentLayer<TComponent>::OnRender(double dt)
{
	EntityComponentSystem* ECS = Application::Get().GetECS();
	ComponentStore<TComponent>* store = ECS->GetComponentStore<TComponent>().value();
	UnorderedVector<TComponent>& components = store->GetComponents();

	for (int i = 0; i < components.size(); i++)
	{
		components[i].OnRender(dt);
	}
}