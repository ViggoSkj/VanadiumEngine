#pragma once
#include "core/CoreTypes.h"


namespace Vanadium
{
	template<typename TComponent>
	class ComponentStore;

	template <typename TComponent>
	class ComponentHandle
	{
	public:
		ComponentHandle(ComponentStore<TComponent>* store, u32 componentId, u32 generation)
			: m_generation(generation)
			, m_store(store)
			, m_componentId(componentId)
		{

		}

		u32 GetId() const;
		TComponent& Get();
	private:
		u32 m_generation;
		u32 m_componentId;
		ComponentStore<TComponent>* m_store;
	};

	template<typename TComponent>
	inline u32 ComponentHandle<TComponent>::GetId() const
	{
		return m_componentId;
	}

	template<typename TComponent>
	inline TComponent& ComponentHandle<TComponent>::Get()
	{
		TComponent* component = m_store->GetComponent(m_componentId);
		assert(component != nullptr);
		return *component;
	}
}