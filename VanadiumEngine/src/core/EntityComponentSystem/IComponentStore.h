#pragma once

struct IComponentStore
{
	IComponentStore() = delete;
	IComponentStore(unsigned int id) : m_id(id) {};

	virtual ~IComponentStore() = default;

	unsigned int GetId() { return m_id; };

private:
	unsigned int m_id;
};