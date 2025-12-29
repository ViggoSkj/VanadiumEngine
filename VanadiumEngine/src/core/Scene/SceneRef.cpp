#include "pch.h"
#include "SceneRef.h"
#include "SceneManager.h"

namespace Vanadium
{
	std::optional<Scene*> SceneRef::GetScene()
	{
		return m_manager->GetScene(m_id);
	}

	Scene& SceneRef::Get()
	{
		return *GetScene().value();
	}
}