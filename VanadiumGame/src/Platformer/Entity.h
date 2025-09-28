#pragma once
#include <memory>
#include <vector>
#include "Component.h"
#include "ComponentStore.h"

inline unsigned int Entity::s_nextId = 1;

struct ComponentAccess
{
	ComponentAccess() = default;
	ComponentAccess(ComponentStore<Component>* store, ComponentRef ref)
		: ComponentStore(store), Ref(ref) {
	};

	ComponentStore<Component>* ComponentStore;
	ComponentRef Ref;
};

class Entity
{
public:
	static unsigned int nextComponentId;

	Entity()
		: m_id(s_nextId++) { };

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	static ComponentStore<TComponent>* GetComponentStore();

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	ComponentRef AddComponent();

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& GetComponent(ComponentRef ref);

	template<typename TComponent>
		requires std::is_base_of_v<Component, TComponent>
	TComponent& GetComponent();

	std::vector<ComponentAccess> m_components;

	unsigned int GetId() const { return m_id; };
private:
	static unsigned int s_nextId;

	unsigned int m_id;
};

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline ComponentStore<TComponent>* Entity::GetComponentStore()
{
	static ComponentStore<TComponent> store;
	return &store;
}

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline ComponentRef Entity::AddComponent()
{
	ComponentStore<TComponent>* store = GetComponentStore<TComponent>();
	ComponentRef ref = store->CreateInstance(e.m_id);
	ComponentAccess a(reinterpret_cast<ComponentStore<Component>*>(store), ref);
	m_components.push_back(a);
	return a.Ref;
}

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline TComponent& Entity::GetComponent(ComponentRef ref)
{
	ComponentStore<TComponent>* store = GetComponentStore<TComponent>();
	return store->GetComponent(ref);
}

template<typename TComponent>
	requires std::is_base_of_v<Component, TComponent>
inline TComponent& Entity::GetComponent()
{
	ComponentStore<TComponent>* store = GetComponentStore<TComponent>();

	for (int i = 0; i < m_components.size(); i++)
	{
		if ((void*)m_components[i].ComponentStore == (void*)store)
			return store->GetComponent(m_components[i].Ref);
	}
	throw "not found";
}

inline unsigned int Entity::nextComponentId = 0;