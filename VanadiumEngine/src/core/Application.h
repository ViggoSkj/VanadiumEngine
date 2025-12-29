#pragma once
#include <memory>
#include "core/Rendering/Window/Window.h"
#include "core/Rendering/RenderingManager.h"
#include "core/AssetManager/AssetManager.h"
#include "core/Time.h"
#include "core/ApplicationLayer.h"
#include "core/EntityComponentSystem/EntityComponentSystem.h"
#include "core/Scene/Scene.h"
#include "core/Scene/SceneManager.h"
#include "core/Debug/Logger.h"

namespace Vanadium
{
	using Vanadium::Detail::Rendering::RenderingManager;

	class Application
	{
	public:
		Application();
		Application(unsigned int width, unsigned int height);
		Application(const Application&) = delete;
		~Application();

		static Application& Get() { return *Application::s_instance; }

		void Run();
		void Stop();

		void PushDefaultPostLayers();

		template <typename TLayer>
			requires(std::is_base_of_v<ApplicationLayer, TLayer>)
		void PushLayer()
		{
			m_applicationLayers.push_back(std::make_unique<TLayer>());
		}

		SceneManager* GetSceneManager() { return m_sceneManager.get(); };
		RenderingManager* GetRenderingManager() { return m_renderingManager.get(); };
		Window* GetWindow() { return m_window.get(); };
		AssetManager* GetAssetManager() { return m_assetManager.get(); }
		EntityComponentSystem* GetECS() { return m_ecs.get(); };
		Logger* GetLogger() { return m_logger.get(); };

		const Time& GetTime() const { return *m_time; }
	private:
		static Application* s_instance;

		std::vector<std::unique_ptr<ApplicationLayer>> m_applicationLayers;
		bool m_running = true;

		// steping mode
		bool m_steppingMode = false;
		bool m_stepBuffered = false;
		float m_stepDt = 0.016f;

		// Modules
		std::unique_ptr<SceneManager> m_sceneManager;
		std::unique_ptr<Window> m_window;
		std::unique_ptr<RenderingManager> m_renderingManager;
		std::unique_ptr<AssetManager> m_assetManager;
		std::unique_ptr<EntityComponentSystem> m_ecs;
		std::unique_ptr<Time> m_time;
		std::unique_ptr<Logger> m_logger;
	};
}