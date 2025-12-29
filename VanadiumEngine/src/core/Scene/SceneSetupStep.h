#pragma once
#include "core/EntityComponentSystem/EntityComponentSystem.h"

namespace Vanadium
{
	class Scene;
	class EntityRef;

	class SceneSetupStep
	{
	public:
		SceneSetupStep(Scene* scene)
			: m_scene(scene)
		{
		}

		virtual ~SceneSetupStep() = default;
		virtual void Execute() {};
		EntityRef CreateEntity();

	private:
		Scene* m_scene;
	};
}