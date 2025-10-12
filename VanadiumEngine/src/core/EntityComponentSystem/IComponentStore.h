#pragma once
#include "pch.h"

struct IComponentStore
{
	IComponentStore() = delete;
	IComponentStore(unsigned int id) : m_id(id) {};

	virtual ~IComponentStore() = default;

	virtual void DeleteInstance(unsigned int id) {};

	unsigned int GetId() { return m_id; };

private:
	unsigned int m_id;
};