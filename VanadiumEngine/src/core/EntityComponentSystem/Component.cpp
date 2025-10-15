#include "pch.h"
#include "Component.h"
#include <iostream>
#include "Application.h"

Component::Component(unsigned int owner)
	: m_id(Component::m_nextId++), m_owner(owner)
{

}

EntityComponentSystem& Component::ECS()
{
	return *Application::Get().GetECS();
}
