#include "pch.h"
#include "Scene.h"
#include "Application.h"
#include "core/Debug/Log.h"

Scene::Scene()
	: m_id(s_nextSceneId++)
{

}

Scene::~Scene()
{
	
}

void Scene::Setup()
{
	LogInfo("Scene setup");
	
	for (int i = 0; i < m_setupSteps.size(); i++)
	{
		m_setupSteps[i]->Execute();
	}

	m_loaded = true;
}

void Scene::Taredown()
{
	LogInfo("Scene taredown");

	EntityComponentSystem* ECS = Application::Get().GetECS();

	while (m_entities.size() > 0)
	{
		ECS->DeleteEntity(m_entities.back());
		m_entities.pop_back();
	}
}

EntityRef Scene::CreateEntity()
{
	EntityRef ref = Application::Get().GetECS()->CreateEntity(SceneRef(m_id, Application::Get().GetSceneManager()));
	m_entities.push_back(ref);
	return ref;
}