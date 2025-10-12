#include "pch.h"
#include "SceneManager.h"
#include "core/Application.h"

Scene& SceneManager::ConstructScene()
{
	m_scenes.emplace_back(Scene{});
	return m_scenes.back();
}

void SceneManager::LoadScene(unsigned int sceneId)
{
	m_commands.emplace(SceneManagerCommand(SceneManagerCommandType::Load, sceneId));
}

void SceneManager::UnloadScene(unsigned int sceneId)
{
	m_commands.emplace(SceneManagerCommand(SceneManagerCommandType::Unload, sceneId));
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

void SceneManager::LoadSceneNow(unsigned int sceneId)
{
	for (int i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i].GetId() == sceneId)
		{
			m_scenes[i].Setup();
		}
	}
}

void SceneManager::UnloadSceneNow(unsigned int sceneId)
{
	for (int i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i].GetId() == sceneId && m_scenes[i].Loaded())
		{
			Application::Get().GetECS()->SignalOwnerDeleted(sceneId);
			m_scenes[i].Taredown();
			break;
		}
	}
}
