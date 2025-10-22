#include "pch.h"
#include "Entity.h"
#include "core/Scene/SceneManager.h"

u32 Entity::GetOwner() const
{
    return m_sceneRef.GetId();
}
