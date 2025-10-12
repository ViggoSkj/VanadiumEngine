#pragma once
#include <memory>

#include <queue>
#include "core/Util/UnorderdVector.h"
#include "Scene.h"

enum SceneManagerCommandType
{
	Load,
	Unload,
};

struct SceneManagerCommand
{
	SceneManagerCommandType Type;
	unsigned int SceneId;
};

class SceneManager
{
public:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;

	Scene& ConstructScene();
	void LoadScene(unsigned int sceneId);
	void UnloadScene(unsigned int sceneId);

	void FlushCommands();

private:
	void LoadSceneNow(unsigned int sceneId);
	void UnloadSceneNow(unsigned int sceneId);


	UnorderedVector<Scene> m_scenes;
	std::queue<SceneManagerCommand> m_commands;
};