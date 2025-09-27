#pragma once



class Component
{
public:
	Component();

	unsigned int GetId() const { return m_id; };
private:
	static unsigned int m_nextId;
	unsigned int m_id;
};

inline unsigned int Component::m_nextId = 0;