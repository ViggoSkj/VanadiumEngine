#pragma once
#include "pch.h"

class SceneManager;
class Scene;

class SceneRef
{
public:
	SceneRef() = default;
	SceneRef(u32 id, SceneManager* manager)
		: m_id(id), m_manager(manager) {
	}

	std::optional<Scene*> GetScene();
	Scene& Get();

	u32 GetId() const { return m_id; }

private:
	SceneManager* m_manager;
	u32 m_id;
};