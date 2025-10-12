#include "pch.h"
#include "SceneSetupStep.h"
#include "core/Application.h"

Entity& SceneSetupStep::CreateEntity()
{
	return Application::Get().GetECS()->CreateEntity(SceneId);
}