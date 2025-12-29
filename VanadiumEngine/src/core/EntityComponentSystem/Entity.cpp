#include "pch.h"
#include "Entity.h"
#include "core/Scene/SceneManager.h"

namespace Vanadium
{
	u32 Entity::GetOwner() const
	{
		return m_sceneRef.GetId();
	}
}