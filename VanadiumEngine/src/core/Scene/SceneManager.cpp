#include "pch.h"
#include "SceneManager.h"
#include "core/Application.h"

namespace Vanadium
{
	SceneRef SceneManager::ConstructScene()
	{
		m_scenes.emplace_back(Scene{});
		return SceneRef(m_scenes.back().GetId(), this);
	}

	void SceneManager::LoadScene(unsigned int sceneId)
	{
		m_commands.emplace(SceneManagerCommand(SceneManagerCommandType::Load, sceneId));
	}

	void SceneManager::UnloadScene(unsigned int sceneId)
	{
		m_commands.emplace(SceneManagerCommand(SceneManagerCommandType::Unload, sceneId));
	}

	void SceneManager::ReloadScene(u32 sceneId)
	{
		m_commands.emplace(SceneManagerCommand(SceneManagerCommandType::Unload, sceneId));
		m_commands.emplace(SceneManagerCommand(SceneManagerCommandType::Load, sceneId));
	}

	void SceneManager::FlushCommands()
	{
		while (m_commands.size() > 0)
		{
			SceneManagerCommand command = m_commands.front();
			switch (command.Type)
			{
			case SceneManagerCommandType::Load:
				LoadSceneNow(command.SceneId);
				break;
			case SceneManagerCommandType::Unload:
				UnloadSceneNow(command.SceneId);
				break;
			}

			m_commands.pop();
		}
	}

	std::optional<Scene*> SceneManager::GetScene(u32 id)
	{
		for (int i = 0; i < m_scenes.size(); i++)
		{
			if (m_scenes[i].GetId() == id)
				return std::optional<Scene*>(&m_scenes[i]);
		}

		return std::nullopt;
	}

	void SceneManager::LoadSceneNow(unsigned int sceneId)
	{
		for (int i = 0; i < m_scenes.size(); i++)
		{
			if (m_scenes[i].GetId() == sceneId)
			{
				m_scenes[i].Setup();
				break;
			}
		}
	}

	void SceneManager::UnloadSceneNow(unsigned int sceneId)
	{
		for (int i = 0; i < m_scenes.size(); i++)
		{
			if (m_scenes[i].GetId() == sceneId && m_scenes[i].Loaded())
			{
				m_scenes[i].Taredown();
				break;
			}
		}
	}

}