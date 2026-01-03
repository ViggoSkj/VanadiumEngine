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
		ComponentHandle()
			: m_componentId(0), m_store(nullptr)
		{

		}

		ComponentHandle(ComponentStore<TComponent>* store, u32 componentId)
			: m_store(store)
			, m_componentId(componentId)
		{

		}

		bool IsEmpty() const;
		u32 GetId() const;
		TComponent& Get();
	private:
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

	template<typename TComponent>
	inline bool ComponentHandle<TComponent>::IsEmpty() const
	{
		if (m_store == nullptr)
			return true;
		return false;
	}
}