#include "pch.h"
#include "EntityRef.h"
#include "EntityComponentSystem.h"

Entity* EntityRef::GetEntity()
{
	return m_system->FindEntity(m_entityId);
}

Entity& EntityRef::Get()
{
	Entity* e = m_system->FindEntity(m_entityId);

#ifndef DEBUG 
	if (e == nullptr)
		throw "Entity is nullptr";
#endif // !DEBUG 


	return *e;
}