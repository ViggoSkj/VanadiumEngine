#include "pch.h"
#include "ComponentStoreManger.h"

namespace Vanadium
{
	void Vanadium::ComponentStoreManager::AwakeComponents()
	{
		for (auto& s : m_stores)
		{
			s->AwakeComponents();
		}
	}
}