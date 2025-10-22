#pragma once
#include "core/EntityComponentSystem/EntityComponentSystem.h"

class Scene;
class EntityRef;

class SceneSetupStep
{
public:
	SceneSetupStep(Scene* scene)
		: m_scene(scene)
	{ }

	virtual ~SceneSetupStep() = default;
	virtual void Execute() {};
protected:

	// helper function
	EntityRef CreateEntity();

private:
	Scene* m_scene;
};