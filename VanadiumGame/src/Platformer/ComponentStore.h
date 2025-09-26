#pragma once
#include "Utility.h"
#include "Component.h"

template <typename TComponent>
	requires(std::is_base_of_v<Component, TComponent>())
class ComponentStore
{	
	TComponent& CreateInstance()
	{
		m_components.PushBack();
		return m_components.PushBack();
	}

private:
	UnorderedVector<TComponent> m_components;
	UnorderedVector<>
};

template <typename TComponent>
	requires(std::is_base_of_v<Component, TComponent>())
class ComponentRef
{
	TComponent* component;
};