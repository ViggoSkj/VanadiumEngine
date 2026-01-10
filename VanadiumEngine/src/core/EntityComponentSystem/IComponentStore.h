#pragma once
#include "pch.h"

namespace Vanadium
{
	struct IComponentStore
	{
		IComponentStore() = delete;
		IComponentStore(unsigned int id) : m_id(id) {};

		virtual ~IComponentStore() = default;

		virtual void DeleteInstance(unsigned int id) {};

		virtual void Flush() {};

		virtual void AwakeComponents() = 0;

		unsigned int GetId() { return m_id; };

	private:
		unsigned int m_id;
	};
}