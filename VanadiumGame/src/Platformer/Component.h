#pragma once



class Component
{
public:
	Component();

	const unsigned int& Id = m_id;

private:
	static unsigned int m_nextId;
	unsigned int m_id;
};