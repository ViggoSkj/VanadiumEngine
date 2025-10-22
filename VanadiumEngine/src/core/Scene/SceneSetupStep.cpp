#include "pch.h"
#include "SceneSetupStep.h"
#include "Scene.h"
#include "core/Application.h"

EntityRef SceneSetupStep::CreateEntity()
{
	return m_scene->CreateEntity();
}