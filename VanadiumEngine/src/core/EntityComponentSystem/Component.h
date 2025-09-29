#pragma once



class Component
{
public:
	Component() = default;
	Component(unsigned int owner);

	unsigned int GetId() const { return m_id; };
	unsigned int GetOwnerId() const { return m_owner; };
private:
	static unsigned int m_nextId;
	unsigned int m_id;
	unsigned int m_owner;
};

inline unsigned int Component::m_nextId = 0;