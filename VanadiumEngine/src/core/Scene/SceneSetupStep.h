#pragma once
#include "core/EntityComponentSystem/Entity.h"

class SceneSetupStep
{
public:
	virtual ~SceneSetupStep() = default;
	virtual void Execute() {};
	
	unsigned int SceneId;
protected:

	// helper function
	Entity& CreateEntity();
};