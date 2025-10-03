#include "Scene.h"

Scene::Scene()
	: m_id(s_nextSceneId++)
{

}

Scene::~Scene()
{
	
}

void Scene::Setup()
{
	for (int i = 0; i < m_setupSteps.size(); i++)
	{
		m_setupSteps[i]->SceneId = m_id;
		m_setupSteps[i]->Execute();
	}

	m_loaded = true;
}

void Scene::Taredown()
{
}
