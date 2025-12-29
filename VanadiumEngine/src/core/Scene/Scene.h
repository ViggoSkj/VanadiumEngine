#pragma once
#include "SceneSetupStep.h"

namespace Vanadium
{
	class EntityRef;

	class Scene
	{
	public:
		Scene(const Scene&) = delete;
		Scene(Scene&&) noexcept = default;
		Scene();
		~Scene();

		template<typename TStep>
			requires std::is_base_of_v<SceneSetupStep, TStep>
		void AddSetupStep()
		{
			m_setupSteps.push_back(std::make_unique<TStep>(this));
		}

		void Setup();
		void Taredown();

		EntityRef CreateEntity();

		unsigned int GetId() { return m_id; };
		bool Loaded() { return m_loaded; };

	private:
		static unsigned int s_nextSceneId;
		unsigned int m_id;
		bool m_loaded = false;

		std::vector<std::unique_ptr<SceneSetupStep>> m_setupSteps;
		UnorderedVector<EntityRef> m_entities;
	};

	inline unsigned int Scene::s_nextSceneId = 1;
}