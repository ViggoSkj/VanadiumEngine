#include "pch.h"
#include "Component.h"
#include <iostream>

Component::Component(unsigned int owner)
	: m_id(Component::m_nextId++), m_owner(owner)
{
}

